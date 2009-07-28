var nile = {};

nile.pipeline = function() {
  var k = arguments[arguments.length - 1];
  for (var i = arguments.length - 2; i >= 0; i--) {
    k = arguments[i](k);
  }
  return k;
};

nile.Echo = function(downstream) {
  return function(input) {
    downstream(input);
  };
};

nile.Interleave2 = function(k1, k2) {
  return function(downstream) {
    return function(input) {
      var out1;
      var out2;
      k1(function(input) { out1 = input })(input.slice(0));
      k2(function(input) { out2 = input })(input);
      var output = [];
      for (var i = 0; i < out1.length; i++)
        output.push(out1[i], out2[i]);
      downstream(output);
    };
  };
};

nile.GroupBy = function(index, size) {
  return function(downstream) {
    return function(input) {
      var buckets = {};
      for (var i = 0; i < input.length; i += size) {
        var v = input.slice(i, size);
        var key = v[index];
        var bucket = buckets[key];
        if (!bucket)
          bucket = buckets[key] = [];
        bucket.push(v);
      }
      for (bucket in buckets) {
        if (buckets.hasOwnProperty(bucket))
          downstream(buckets[bucket]);
      }
    };
  };
};

nile.SortBy = function(index, size) {
  return function(downstream) {
    return function(input) {
      var vectors = [];
      for (var i = 0; i < input.length; i += size)
        vectors.push(input.slice(i, size));
      vectors.sort(function(a, b) {
        if (a[index] < b[index])
          return -1;
        else if (a[index] > b[index])
          return 1;
        else
          return 0;
      });
      downstream(input);
    };
  };
};
