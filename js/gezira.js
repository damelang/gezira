var gezira = {};

/* Host-supplied kernels */

gezira.ReadImage = function(image) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var data = image.data;
      while (input.length) {
        var x = input.shift();
        var y = input.shift();
        var i = (Math.floor(x) + Math.floor(y) * image.width) * 4;
        var a = data[i + 3] / 255;
        var r = data[i + 0] / 255 * a;
        var g = data[i + 1] / 255 * a;
        var b = data[i + 2] / 255 * a;
        output.push(a, r, g, b);
      }
      downstream(output);
    };
  };
};

gezira.WriteImage = function(image) {
  return function(x, y) {
    return function(downstream) {
      return function(input) {
        var data = image.data;
        var i = (Math.floor(x) + Math.floor(y) * image.width) * 4;
        for (; input.length; i += 4) {
          var s_a = input.shift();
          var s_r = input.shift();
          var s_g = input.shift();
          var s_b = input.shift();
          var m = input.shift();
          var d_a = data[i + 3] / 255;
          var d_r = data[i + 0] / 255 * d_a;
          var d_g = data[i + 1] / 255 * d_a;
          var d_b = data[i + 2] / 255 * d_a;
          var r_a = m * s_a + (1 - m) * d_a;
          var r_r = m * s_r + (1 - m) * d_r;
          var r_g = m * s_g + (1 - m) * d_g;
          var r_b = m * s_b + (1 - m) * d_b;
          data[i + 3] = r_a * 255;
          data[i + 0] = r_r / r_a * 255;
          data[i + 1] = r_g / r_a * 255;
          data[i + 2] = r_b / r_a * 255;
        }
      };
    };
  };
};

/* core.nl */

gezira.CompositeSamplers = function(s1, s2, c) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        var f = Pipeline(Interleave(s1, 4, s2, 4), c);
        f(downstream)(input);
      } }
    };
  };
};

gezira.UniformColor = function(c_a, c_r, c_g, c_b) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var p_x = input.shift();
        var p_y = input.shift();
        output.push(c_a, c_r * c_a, c_g * c_a, c_b * c_a);
      }
      downstream(output);
    };
  };
};

gezira.CompositeOver = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a + b_a * (1 - a_a);
      var _1_r = a_r + b_r * (1 - a_a);
      var _1_g = a_g + b_g * (1 - a_a);
      var _1_b = a_b + b_b * (1 - a_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.FillBetweenEdges = function(start_x, start_y) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var x = start_x;
      var local = 0;
      var run = 0;
      while (input.length) {
        var local_, run_;
        var x_ = input.shift();
        var y = input.shift();
        var w = input.shift();
        var h = input.shift();
        run_ = run + h;
        var n = x_ - x;
        if (n == 0) {
          local_ = local + w * h;
        } else {
          local_ = run + w * h;
          var _1 = Math.abs(local);
          var _2 = _1 < 1 ? _1 : 1;
          output.push(_2);
          var _3 = Math.abs(run);
          var _4 = _3 < 1 ? _3 : 1;
          for (var i = 0; i < (n - 1); i++)
            output.push(_4);
        }
        x = x_;
        local = local_;
        run = run_;
      }
      if (local != 0) {
        var _5 = Math.abs(local);
        var _6 = _5 < 1 ? _5 : 1;
        output.push(_6);
      }
      downstream(output);
    };
  };
};

gezira.CreateSamplePoints = function(start_x, start_y) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var x = start_x;
      var y = start_y;
      while (input.length) {
        var x_;
        var c = input.shift();
        x_ = x + 1;
        output.push(x, y);
        x = x_;
      }
      downstream(output);
    };
  };
};

gezira.Render_ = function(s, c) {
  return function(downstream) {
    return function(input) {
      var p_x = input[0];
      var p_y = input[1];
      var w = input[2];
      var h = input[3];
      with (gezira) { with (nile) {
        var f = Pipeline(
          FillBetweenEdges(p_x, p_y),
          Interleave(Pipeline(CreateSamplePoints(p_x + 0.5, p_y + 0.5), s), 4,
                     Pipeline(), 1),
          c(p_x + 0.5, p_y + 0.5));
        f(downstream)(input);
      } }
    };
  };
};

gezira.Render = function(s, c) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        var f = GroupBy(1, 4, Pipeline(SortBy(0, 4), Render_(s, c)));
        f(downstream)(input);
      } }
    };
  };
};

/* bezier.nl */

gezira.TransformBezier = function(m_a, m_b, m_c, m_d, m_e, m_f) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var a_x = input.shift();
        var a_y = input.shift();
        var b_x = input.shift();
        var b_y = input.shift();
        var c_x = input.shift();
        var c_y = input.shift();
        var _1_x = m_a * a_x + m_c * a_y + m_e;
        var _1_y = m_b * a_x + m_d * a_y + m_f;
        var _2_x = m_a * b_x + m_c * b_y + m_e;
        var _2_y = m_b * b_x + m_d * b_y + m_f;
        var _3_x = m_a * c_x + m_c * c_y + m_e;
        var _3_y = m_b * c_x + m_d * c_y + m_f;
        output.push(_1_x, _1_y, _2_x, _2_y, _3_x, _3_y);
      }
      downstream(output);
    };
  };
};

gezira.ClipBezier = function(min_x, min_y, max_x, max_y) {
  return function(downstream) {
    return function(input) {
      var output = [];
      debugger;
      while (input.length) {
        var a_x = input.shift();
        var a_y = input.shift();
        var b_x = input.shift();
        var b_y = input.shift();
        var c_x = input.shift();
        var c_y = input.shift();
        var _1_x = a_x < b_x ? a_x : b_x;
        var _1_y = a_y < b_y ? a_y : b_y;
        var bmin_x = _1_x < c_x ? _1_x : c_x;
        var bmin_y = _1_y < c_y ? _1_y : c_y;
        var _2_x = a_x > b_x ? a_x : b_x;
        var _2_y = a_y > b_y ? a_y : b_y;
        var bmax_x = _2_x > c_x ? _2_x : c_x;
        var bmax_y = _2_y > c_y ? _2_y : c_y;
        var _3_0 = min_x <= bmin_x;
        var _3_1 = min_y <= bmin_y;
        var _4_0 = bmax_x <= max_x;
        var _4_1 = bmax_y <= max_y;
        var _5_0 = _3_0 && _4_0;
        var _5_1 = _3_1 && _4_1;
        var _6 = _5_0 && _5_1;
        var _7_0 = bmax_x <= min_x;
        var _7_1 = bmax_y <= min_y;
        var _8_0 = max_x <= bmin_x;
        var _8_1 = max_y <= bmin_y;
        var _9_0 = _7_0 || _8_0;
        var _9_1 = _7_1 || _8_1;
        var _10 = _9_0 || _9_1;
        if (_6) {
          output.push(a_x, a_y, b_x, b_y, c_x, c_y);
        }
        else if (_10) {
          var _11_x = min_x > a_x ? min_x : a_x;
          var _11_y = min_y > a_y ? min_y : a_y;
          var ca_x = _11_x < max_x ? _11_x : max_x;
          var ca_y = _11_y < max_y ? _11_y : max_y;
          var _12_x = min_x > c_x ? min_x : c_x;
          var _12_y = min_y > c_y ? min_y : c_y;
          var cc_x = _12_x < max_x ? _12_x : max_x;
          var cc_y = _12_y < max_y ? _12_y : max_y;
          output.push(ca_x, ca_y, (ca_x + cc_x) / 2, (ca_y + cc_y) / 2,
                      cc_x, cc_y);
        }
        else {
          var abbc_x = (((a_x + b_x) / 2) + ((b_x + c_x) / 2)) / 2;
          var abbc_y = (((a_y + b_y) / 2) + ((b_y + c_y) / 2)) / 2;
          var _9_x = Math.abs(abbc_x - min_x);
          var _9_y = Math.abs(abbc_y - min_y);
          var nearmin_0 = _9_x < 0.1;
          var nearmin_1 = _9_y < 0.1;
          var _11_x = Math.abs(abbc_x - max_x);
          var _11_y = Math.abs(abbc_y - max_y);
          var nearmax_0 = _11_x < 0.1;
          var nearmax_1 = _11_y < 0.1;
          var m_x = nearmin_0 ? min_x : (nearmax_0 ? max_x : abbc_x);
          var m_y = nearmin_1 ? min_y : (nearmax_1 ? max_y : abbc_y);
          input.unshift(a_x, a_y, (a_x + b_x) / 2, (a_y + b_y) / 2, m_x, m_y,
                        m_x, m_y, (b_x + c_x) / 2, (b_y + c_y) / 2, c_x, c_y);
        }
      }
      downstream(output);
    };
  };
};

gezira.DecomposeBezier = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_x = input.shift();
      var a_y = input.shift();
      var b_x = input.shift();
      var b_y = input.shift();
      var c_x = input.shift();
      var c_y = input.shift();
      var _1_x = Math.floor(a_x);
      var _1_y = Math.floor(a_y);
      var _2_x = Math.floor(c_x);
      var _2_y = Math.floor(c_y);
      var _3_x = Math.ceil(a_x);
      var _3_y = Math.ceil(a_y);
      var _4_x = Math.ceil(c_x);
      var _4_y = Math.ceil(c_y);
      var _5_0 = _1_x == _2_x;
      var _5_1 = _1_y == _2_y;
      var _6_0 = _3_x == _4_x;
      var _6_1 = _3_y == _4_y;
      var _7_0 = _5_0 || _6_0;
      var _7_1 = _5_1 || _6_1;
      var _8 = _7_0 && _7_1;
      if (_8) {
        var p_x = _1_x < _2_x ? _1_x : _2_x;
        var p_y = _1_y < _2_y ? _1_y : _2_y;
        var w = p_x + 1 - ((c_x + a_x) / 2);
        var h = c_y - a_y;
        output.push(p_x, p_y, w, h);
      }
      else {
        var abbc_x = (((a_x + b_x) / 2) + ((b_x + c_x) / 2)) / 2;
        var abbc_y = (((a_y + b_y) / 2) + ((b_y + c_y) / 2)) / 2;
        var min_x = Math.floor(abbc_x);
        var min_y = Math.floor(abbc_y);
        var max_x = Math.ceil(abbc_x);
        var max_y = Math.ceil(abbc_y);
        var _9_x = Math.abs(abbc_x - min_x);
        var _9_y = Math.abs(abbc_y - min_y);
        var nearmin_0 = _9_x < 0.1;
        var nearmin_1 = _9_y < 0.1;
        var _11_x = Math.abs(abbc_x - max_x);
        var _11_y = Math.abs(abbc_y - max_y);
        var nearmax_0 = _11_x < 0.1;
        var nearmax_1 = _11_y < 0.1;
        var m_x = nearmin_0 ? min_x : (nearmax_0 ? max_x : abbc_x);
        var m_y = nearmin_1 ? min_y : (nearmax_1 ? max_y : abbc_y);
        input.unshift(a_x, a_y, (a_x + b_x) / 2, (a_y + b_y) / 2, m_x, m_y,
                      m_x, m_y, (b_x + c_x) / 2, (b_y + c_y) / 2, c_x, c_y);
      }
    }
    downstream(output);
  };
};

/* sampler.nl */

/* TODO Image stuff */

gezira.LinearGradientShape = function(s00, ds_dx, ds_dy) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var x = input.shift();
        var y = input.shift();
        var _1 = s00 + x * ds_dx + y * ds_dy;
        output.push(_1);
      }
      downstream(output);
    };
  };
};

gezira.RadialGradientShape = function(c_x, c_y, r) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var p_x = input.shift();
        var p_y = input.shift();
        var d_x = p_x - c_x;
        var d_y = p_y - c_y;
        var _1 = Math.sqrt(d_x * d_x + d_y * d_y) / r
        output.push(_1);
      };
      downstream(output);
    };
  };
};

gezira.GradientExtendPad = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var s = input.shift();
      var _1 = 0 > s ? 0 : s;
      var _2 = _1 < 1 ? _1 : 1;
      output.push(_2);
    }
    downstream(output);
  };
};

gezira.GradientExtendRepeat = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var s = input.shift();
      var _1 = s - Math.floor(s);
      output.push(_1);
    }
    downstream(output);
  };
};

gezira.GradientExtendMirror = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var s = input.shift();
      var _1 = Math.abs(s) % 2;
      var _2 = Math.abs(_1 - 1);
      var _3 = 1 - _2;
      output.push(_3);
    }
    downstream(output);
  };
};

gezira.GradientColorBegin = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var s = input.shift();
      output.push(s, 0, 0, 0, 0);
    }
    downstream(output);
  };
};

gezira.GradientColorSpan = function(c0_a, c0_r, c0_g, c0_b,
                                    dc_ds_a, dc_ds_r, dc_ds_g, dc_ds_b, l) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var s = input.shift();
        var c_a = input.shift();
        var c_r = input.shift();
        var c_g = input.shift();
        var c_b = input.shift();
        var d_a = c0_a + s * dc_ds_a;
        var d_r = c0_r + s * dc_ds_r;
        var d_g = c0_g + s * dc_ds_g;
        var d_b = c0_b + s * dc_ds_b;
        var _1_a = s < 0 ? c_a : d_a;
        var _1_r = s < 0 ? c_r : d_r;
        var _1_g = s < 0 ? c_g : d_g;
        var _1_b = s < 0 ? c_b : d_b;
        output.push(s - l, _1_a, _1_r, _1_g, _1_b);
      }
      downstream(output);
    };
  };
};

gezira.GradientColorEnd = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var s = input.shift();
      var c_a = input.shift();
      var c_r = input.shift();
      var c_g = input.shift();
      var c_b = input.shift();
      output.push(c_a, c_r * c_a, c_g * c_a, c_b * c_a);
    }
    downstream(output);
  };
};

gezira.Gradient = function(s, e, c) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        var f = Pipeline(s, e, GradientColorBegin, c, GradientColorEnd);
        f(downstream)(input);
      } }
    };
  };
};

/* stroke.nl */

// have to cheat here...
gezira.norm = function(a_x, a_y) {
  return Math.sqrt(a_x * a_x + a_y * a_y);
};
gezira.perp = function(a_x, a_y, b_x, b_y) {
  var _1_x = b_x - a_x;
  var _1_y = b_y - a_y;
  // || b - a ||
  var _2 = gezira.norm(_1_x, _1_y);
  // ^(b - a)
  var _3_x = _2 != 0 ? _1_x / _2 : _1_x;
  var _3_y = _2 != 0 ? _1_y / _2 : _1_y;
  var _4_x = 0 - _3_y;
  var _4_y = _3_x;
  return [_4_x, _4_y];
};

gezira.StrokeCapButt = function(o) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var a_x = input[0];
      var a_y = input[1];
      var b_x = input[2];
      var b_y = input[3];
      var c_x = input[4];
      var c_y = input[5];
      var a_b = gezira.perp(a_x, a_y, b_x, b_y);
      var _5_x = a_b[0] * o;
      var _5_y = a_b[1] * o;
      var _6_x = a_x - _5_x;
      var _6_y = a_y - _5_y;
      var _7_x = a_x + _5_x;
      var _7_y = a_y + _5_y;
      output.push(_6_x, _6_y, a_x, a_y, _7_x, _7_y);
      downstream(output);
    };
  };
};

gezira.StrokeJoinBevel = function(o) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var a_x = input.shift();
      var a_y = input.shift();
      var b_x = input.shift();
      var b_y = input.shift();
      var c_x = input.shift();
      var c_y = input.shift();
      while (input.length) {
        var d_x = input.shift();
        var d_y = input.shift();
        var e_x = input.shift();
        var e_y = input.shift();
        var f_x = input.shift();
        var f_y = input.shift();
        var b_c = gezira.perp(b_x, b_y, c_x, c_y);
        var g_x = c_x + b_c[0] * o;
        var g_y = c_y + b_c[1] * o;
        var d_e = gezira.perp(d_x, d_y, e_x, e_y);
        var h_x = d_x + d_e[0] * o;
        var h_y = d_y + d_e[1] * o;
        output.push(g_x, g_y, (g_x + h_x) / 2, (g_y + h_y) / 2, h_x, h_y);
        a_x = d_x; a_y = d_y;
        b_x = e_x; b_y = e_y;
        c_x = f_x; c_y = f_y;
      }
      downstream(output);
    };
  };
};

/* TODO this looks OK for the examples I've tried */
gezira.stroke_error = 0.03;

gezira.StrokeOffsetCurve = function(o) {
  return function(downstream) {
    return function(input) {
      var output = [];
      while (input.length) {
        var a_x = input.shift();
        var a_y = input.shift();
        var b_x = input.shift();
        var b_y = input.shift();
        var c_x = input.shift();
        var c_y = input.shift();
        var a_b = gezira.perp(a_x, a_y, b_x, b_y);
        var d_x = a_x + a_b[0] * o;
        var d_y = a_y + a_b[1] * o;
        var b_c = gezira.perp(b_x, b_y, c_x, c_y);
        var f_x = c_x + b_c[0] * o;
        var f_y = c_y + b_c[1] * o;
        var m_x = (((a_x + b_x) / 2) + ((b_x + c_x) / 2)) / 2;
        var m_y = (((a_y + b_y) / 2) + ((b_y + c_y) / 2)) / 2;
        var n_x = m_x + ((a_b[0] + b_c[0]) / 2) * o;
        var n_y = m_y + ((a_b[1] + b_c[1]) / 2) * o;
        var e_x = 2 * n_x - 0.5 * d_x - 0.5 * f_x;
        var e_y = 2 * n_y - 0.5 * d_y - 0.5 * f_y;
        var d_e = gezira.perp(d_x, d_y, e_x, e_y);
        var e_f = gezira.perp(e_x, e_y, f_x, f_y);
        var error = gezira.norm(a_b[0] - d_e[0], a_b[1] - d_e[1]) +
                    gezira.norm(b_c[0] - e_f[0], b_c[1] - e_f[1]);
        if (error < gezira.stroke_error)
          output.push(d_x, d_y, e_x, e_y, f_x, f_y);
        else {
          input.unshift(a_x, a_y, (a_x + b_x) / 2, (a_y + b_y) / 2, m_x, m_y,
                        m_x, m_y, (b_x + c_x) / 2, (b_y + c_y) / 2, c_x, c_y);
        }
      }
      downstream(output);
    };
  };
};

gezira.StrokeSide = function(c, j, o) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        var f = Mix(StrokeOffsetCurve(o), Mix(c(o), j(o)));
        f(downstream)(input);
      } }
    };
  };
};

gezira.ReverseBezier = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_x = input.shift();
      var a_y = input.shift();
      var b_x = input.shift();
      var b_y = input.shift();
      var c_x = input.shift();
      var c_y = input.shift();
      output.push(c_x, c_y, b_x, b_y, a_x, a_y);
    }
    downstream(output);
  };
};

gezira.Stroke = function(c, j, o) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        var f = Mix(
          StrokeSide(c, j, o),
          Pipeline(ReverseBezier, Reverse(6), StrokeSide(c, j, o)));
        f(downstream)(input);
      } }
    };
  };
};

/* compositor.nl */

gezira.CompositeClear = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      output.push(0, 0, 0, 0);
    }
    downstream(output);
  };
};

gezira.CompositeSrc = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      output.push(a_a, a_r, a_g, a_b);
    }
    downstream(output);
  };
};

gezira.CompositeDst = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      output.push(b_a, b_r, b_g, b_b);
    }
    downstream(output);
  };
};


gezira.CompositeDstOver = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = b_a + a_a * (1 - b_a);
      var _1_r = b_r + a_r * (1 - b_a);
      var _1_g = b_g + a_g * (1 - b_a);
      var _1_b = b_b + a_b * (1 - b_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeSrcIn = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a * b_a;
      var _1_r = a_r * b_a;
      var _1_g = a_g * b_a;
      var _1_b = a_b * b_a;
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeDstIn = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = b_a * a_a;
      var _1_r = b_r * a_a;
      var _1_g = b_g * a_a;
      var _1_b = b_b * a_a;
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeSrcOut = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a * (1 - b_a);
      var _1_r = a_r * (1 - b_a);
      var _1_g = a_g * (1 - b_a);
      var _1_b = a_b * (1 - b_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeDstOut = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = b_a * (1 - a_a);
      var _1_r = b_r * (1 - a_a);
      var _1_g = b_g * (1 - a_a);
      var _1_b = a_b * (1 - a_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeSrcAtop = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a * b_a + b_a * (1 - a_a);
      var _1_r = a_r * b_a + b_r * (1 - a_a);
      var _1_g = a_g * b_a + b_g * (1 - a_a);
      var _1_b = a_b * b_a + b_b * (1 - a_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeDstAtop = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = b_a * a_a + a_a * (1 - b_a);
      var _1_r = b_r * a_a + a_r * (1 - b_a);
      var _1_g = b_g * a_a + a_g * (1 - b_a);
      var _1_b = b_b * a_a + a_b * (1 - b_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositeXor = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a * (1 - b_a) + b_a * (1 - a_a);
      var _1_r = a_r * (1 - b_a) + b_r * (1 - a_a);
      var _1_g = a_g * (1 - b_a) + b_g * (1 - a_a);
      var _1_b = a_b * (1 - b_a) + b_b * (1 - a_a);
      output.push(_1_a, _1_r, _1_g, _1_b);
    }
    downstream(output);
  };
};

gezira.CompositePlus = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a + b_a;
      var _1_r = a_r + b_r;
      var _1_g = a_g + b_g;
      var _1_b = a_b + b_b;
      var _2_a = _1_a < 1 ? _1_a : 1;
      var _2_r = _1_r < 1 ? _1_r : 1;
      var _2_g = _1_g < 1 ? _1_g : 1;
      var _2_b = _1_b < 1 ? _1_b : 1;
      output.push(_2_a, _2_r, _2_g, _2_b);
    }
    downstream(output);
  };
};
        
gezira.CompositeMultiply = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a * (1 - b_a) + b_a * (1 - a_a)
      var _1_r = a_r * (1 - b_a) + b_r * (1 - a_a)
      var _1_g = a_g * (1 - b_a) + b_g * (1 - a_a)
      var _1_b = a_b * (1 - b_a) + b_b * (1 - a_a)
      var _2_a = a_a * b_a + _1_a;
      var _2_r = a_r * b_r + _1_r;
      var _2_g = a_g * b_g + _1_g;
      var _2_b = a_b * b_b + _1_b;
      output.push(_2_a, _2_r, _2_g, _2_b);
    }
    downstream(output);
  };
};

gezira.CompositeScreen = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a + b_a;
      var _1_r = a_r + b_r;
      var _1_g = a_g + b_g;
      var _1_b = a_b + b_b;
      var _2_a = a_a * b_a;
      var _2_r = a_r * b_r;
      var _2_g = a_g * b_g;
      var _2_b = a_b * b_b;
      var _3_a = _1_a - _2_a;
      var _3_r = _1_r - _2_r;
      var _3_g = _1_g - _2_g;
      var _3_b = _1_b - _2_b;
      output.push(_3_a, _3_r, _3_g, _3_b);
    }
    downstream(output);
  };
};

/* TODO

CompositeOverlay

CompositeDarken

CompositeLighten

CompositeColorDodge

CompositeColorBurn

CompositeHardLight

CompositeSoftLight

CompositeDifference

CompositeExclusion

*/

gezira.CompositeSubtract = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      var _1_a = a_a + b_a - 1;
      var _1_r = a_r + b_r - 1;
      var _1_g = a_g + b_g - 1;
      var _1_b = a_b + b_b - 1;
      var _2_a = _1_a > 0 ? _1_a : 0;
      var _2_r = _1_r > 0 ? _1_r : 0;
      var _2_g = _1_g > 0 ? _1_g : 0;
      var _2_b = _1_b > 0 ? _1_b : 0;
      output.push(_2_a, _2_r, _2_g, _2_b);
    }
    downstream(output);
  };
};

gezira.CompositeInvert = function(downstream) {
  return function(input) {
    var output = [];
    while (input.length) {
      var a_a = input.shift();
      var a_r = input.shift();
      var a_g = input.shift();
      var a_b = input.shift();
      var b_a = input.shift();
      var b_r = input.shift();
      var b_g = input.shift();
      var b_b = input.shift();
      output.push(b_a, 1 - b_r, 1 - b_g, 1 - b_b);
    }
    downstream(output);
  };
};
