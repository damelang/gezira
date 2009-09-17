var nile = {};

nile.debug = function(s) {
  return;
  document.body.appendChild(document.createElement('div')).innerHTML = s;
};

nile.pipeline = function() {
  var k = arguments[arguments.length - 1];
  for (var i = arguments.length - 2; i >= 0; i--)
    k = arguments[i](k);
  return k;
};

nile.combine = function() {
  var ks = Array.prototype.slice.call(arguments);
  return function(downstream) {
    return nile.pipeline.apply(null, ks.concat(downstream))
  };
};

nile.Id = function(downstream) {
  return function(input) {
    downstream(input);
  };
};

nile.Interleave = function(k1, size1, k2, size2) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var out1;
      var out2;
      k1(function(input) { out1 = input })(input.slice(0));
      k2(function(input) { out2 = input })(input);
      var outputsize = out1.length / size1;
      for (var i = 0; i < outputsize; i++) {
        for (var j = 0; j < size1; j++)
          output.push(out1[i * size1 + j]);
        for (var j = 0; j < size2; j++)
          output.push(out2[i * size2 + j]);
      }
      downstream(output);
    };
  };
};

nile.Mix = function(k1, k2, k3, k4) {
  return function(downstream) {
    return function(input) {
      var o1, o2, o3, o4;
      k1(function(input) { o1 = input })(input.slice(0));
      k2(function(input) { o2 = input })(input.slice(0));
      k3(function(input) { o3 = input })(input.slice(0));
      k4(function(input) { o4 = input })(input.slice(0));
      downstream(o1.concat(o2).concat(o3).concat(o4));
    };
  };
};

nile.GroupBy = function(index, size) {
  return function(downstream) {
    return function(input) {
      var buckets = {};
      for (var i = 0; i < input.length; i += size) {
        var key = input[i + index];
        var bucket = buckets[key];
        if (!bucket)
          bucket = buckets[key] = [];
        for (var j = 0; j < size; j++)
          bucket.push(input[i + j]);
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
        vectors.push(input.slice(i, i + size));
      vectors.sort(function(a, b) {
        if (a[index] < b[index])
          return -1;
        else if (a[index] > b[index])
          return 1;
        else
          return 0;
      });
      var output = [];
      for (var i = 0; i < vectors.length; i++)
        for (var j = 0; j < size; j++)
          output.push(vectors[i][j]);
      downstream(output);
    };
  };
};
