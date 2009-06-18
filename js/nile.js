var nile = {};

nile.pipeline = function() {
  var k = arguments[arguments.length - 1];
  for (var i = arguments.length - 2; i >= 0; i--) {
    k = arguments[i](k);
  }
  return k;
};

nile.Interleave2 = function(k1, k2) {
  return function(downstream) {
    return function(input) {
      var k1_out;
      var k2_out;
      var k2_input = input.slice(0);
      k1(function(input) { k1_out = input })(input);
      k2(function(input) { k2_out = input })(k2_input);
      var i = 0;
      var output = k1_out.map(function(o1) {
        return [o1, k2_out[i++]];
      });
      downstream(output);
    };
  };
};

nile.GroupBy = function(f) {
  return function(downstream) {
    return function(input) {
      var buckets = {};
      while (input.length) {
        var element = input.shift();
        var key = f(element);
        var bucket = buckets[key];
        if (!bucket)
          bucket = buckets[key] = [];
        bucket.push(element);
      }
      for (bucket in buckets) {
        if (buckets.hasOwnProperty(bucket))
          downstream(buckets[bucket]);
      }
    };
  };
};

nile.SortBy = function(f) {
  return function(downstream) {
    return function(input) {
      input.sort(function(a, b) {
        var fa = f(a);
        var fb = f(b);
        if (fa < fb)
          return -1;
        else if (fa > fb)
          return 1;
        else
          return 0;
      });
      downstream(input);
    };
  };
};
