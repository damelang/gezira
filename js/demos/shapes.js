var shapes = {};

// Thanks, Jeff!
shapes.star = function(c_x, c_y, r0, r1, n) {
  var points = [];
  for (var i = 0; i < n; i++) {
    // Outer point
    var angle = i * 2 * Math.PI / n;
    var x = c_x - Math.sin(angle) * r1;
    var y = c_y - Math.cos(angle) * r1;
    points.push(x, y, x, y, x, y);

    // Inner point
    angle = i * 2 * Math.PI / n + 2 * Math.PI / (n * 2);
    x = c_x - Math.sin(angle) * r0;
    y = c_y - Math.cos(angle) * r0;
    points.push(x, y, x, y, x, y);
  }
  points.push(points.shift());
  points.push(points.shift());

  /* TODO this better */
  for (var i = 0; i < points.length; i += 6) {
    var a_x = points[i];
    var a_y = points[i + 1];
    var c_x_ = points[i + 4];
    var c_y_ = points[i + 5];
    points[i + 2] = (a_x + c_x_) / 2;
    points[i + 3] = (a_y + c_y_) / 2;
  }
  return points;
};

shapes.centeredStar = function(image) {
  return shapes.star(image.width / 2, image.height / 2, 42, 100, 5);
};
