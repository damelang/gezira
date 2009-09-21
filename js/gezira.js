var gezira = {};

/* Host-supplied kernels */

gezira.ReadImage = function(image) {
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        var output = [];
        var data = image.data;
        var i = (image.width * Math.floor(start_y) + Math.floor(start_x)) * 4;
        for (var end = i + input.length * 4; i != end; i += 4) {
          var a = data[i + 3] / 255;
          output.push(a, data[i + 0] / 255 * a,
                         data[i + 1] / 255 * a,
                         data[i + 2] / 255 * a);
        }
        downstream(output);
      };
    };
  };
};

gezira.WriteImage = function(image) {
  return function(start_x, start_y) {
    return function(input) {
      var data = image.data;
      var i = (image.width * Math.floor(start_y) + Math.floor(start_x)) * 4;
      for (; input.length; i += 4) {
        var c_a = input.shift();
        var c_r = input.shift();
        var c_g = input.shift();
        var c_b = input.shift();
        var a = input.shift();
        var d_a = data[i + 3] / 255;
        var d_r = data[i + 0] / 255 * d_a;
        var d_g = data[i + 1] / 255 * d_a;
        var d_b = data[i + 2] / 255 * d_a;
        var r_a = a * c_a + (1 - a) * d_a;
        var r_r = a * c_r + (1 - a) * d_r;
        var r_g = a * c_g + (1 - a) * d_g;
        var r_b = a * c_b + (1 - a) * d_b;
        data[i + 3] = r_a * 255;
        data[i + 0] = r_r / r_a * 255;
        data[i + 1] = r_g / r_a * 255;
        data[i + 2] = r_b / r_a * 255;
      }
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
      /* TODO */
      /* See Josh Gargus' bug fixes for the old version */
      alert("TODO");
      die();
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

/* gradient.nl */

gezira.LinearGradient = function(s00, ds_dx, ds_dy) {
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        var output = [];
        var s_, s = s00 + start_x * ds_dx + start_y * ds_dy;
        while (input.length) {
          var _ = input.shift();
          s_ = s + ds_dx;
          output.push(s);
          s = s_;
        }
        downstream(output);
      };
    };
  };
};

gezira.RadialGradient = function(c_x, c_y, r) {
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        var output = [];
        var x_, x = start_x;
        var dy2 = (start_y - c_y) * (start_y - c_y);
        while (input.length) {
          var _ = input.shift();
          x_ = x + 1;
          output.push(Math.sqrt((x - c_x) * (x - c_x) + dy2) / r);
          x = x_;
        };
        downstream(output);
      };
    };
  };
};

gezira.GradientPad = function(downstream) {
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

gezira.GradientRepeat = function(downstream) {
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

gezira.GradientMirror = function(downstream) {
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
      var _ = input.shift();
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
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        with (gezira) { with (nile) {
          pipeline(s(start_x, start_y), e, GradientColorBegin, c, GradientColorEnd,
                   downstream)(input);
        } }
      };
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

/*
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

/* stroke.nl */

gezira.StrokeCapButt = function(o) {
  return function(downstream) {
    return function(input) {
      var input = input.slice(0, 6).concat(input.slice(-6));
      var output = [];
      while (input.length) {
        var a_x = input.shift();
        var a_y = input.shift();
        var b_x = input.shift();
        var b_y = input.shift();
        var c_x = input.shift();
        var c_y = input.shift();
        var _1_x = b_x - a_x;
        var _1_y = b_y - a_y;
        var _2 = Math.sqrt(_1_x * _1_x + _1_y * _1_y);
        var ab_x = _1_x / _2;
        var ab_y = _1_y / _2;
        var _3_x = 0 - ab_y;
        var _3_y = ab_x;
        var _4_x = a_x - _3_x * o;
        var _4_y = a_y - _3_y * o;
        var _5_x = a_x + _3_x * o;
        var _5_y = a_y + _3_y * o;
        output.push(_4_x, _4_y, a_x, a_y, _5_x, _5_y);
      }
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
        var _1_x = c_x - b_x;
        var _1_y = c_y - b_y;
        var _2 = Math.sqrt(_1_x * _1_x + _1_y * _1_y);
        var bc_x = _1_x / _2;
        var bc_y = _1_y / _2;

        var _3_x = e_x - d_x;
        var _3_y = e_y - d_y;
        var _4 = Math.sqrt(_3_x * _3_x + _3_y * _3_y);
        var de_x = _3_x / _4;
        var de_y = _3_y / _4;

        var _5_x = 0 - bc_y;
        var _5_y = bc_x;
        var f_x = c_x + _5_x * o;
        var f_y = c_y + _5_y * o;

        var _6_x = 0 - de_y;
        var _6_y = de_x;
        var g_x = d_x + _6_x * o;
        var g_y = d_y + _6_y * o;

        var h_x = d_x - _6_x * o;
        var h_y = d_y - _6_y * o;

        var i_x = c_x - _5_x * o;
        var i_y = c_y - _5_y * o;

        var _7_x = (f_x + g_x) / 2;
        var _7_y = (f_y + g_y) / 2;
        var _8_x = (h_x + i_x) / 2;
        var _8_y = (h_y + i_y) / 2;
        output.push(f_x, f_y, _7_x, _7_y, g_x, g_y);
        output.push(h_x, h_y, _8_x, _8_y, i_x, i_y);
        a = d; b = e; c = f;
      }
      downstream(output);
    };
  };
};

gezira.StrokeOutline = function(o) {
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

        var _1_x = b_x - a_x;
        var _1_y = b_y - a_y;
        var _2 = Math.sqrt(_1_x * _1_x + _1_y * _1_y);
        var ab_x = _1_x / _2;
        var ab_y = _1_y / _2;

        var _3_x = c_x - b_x;
        var _3_y = c_y - b_y;
        var _4 = Math.sqrt(_3_x * _3_x + _3_y * _3_y);
        var bc_x = _3_x / _4;
        var bc_y = _3_y / _4;

        // ⟂(ab)
        var _5_x = 0 - ab_y;
        var _5_y = ab_x;

        var d_x = a_x + _5_x * o;
        var d_y = a_y + _5_y * o;

        // ⟂(bc)
        var _6_x = 0 - bc_y;
        var _6_y = bc_x;

        var f_x = c_x + _6_x * o;
        var f_y = c_y + _6_y * o;

        // a ~~ b
        var _7_x = (a_x + b_x) / 2;
        var _7_y = (a_y + b_y) / 2;

        // b ~~ c
        var _8_x = (b_x + c_x) / 2;
        var _8_y = (b_y + c_y) / 2;

        var m_x = (_7_x + _8_x) / 2;
        var m_y = (_7_y + _8_y) / 2;

        // ⟂(ab) ~~ ⟂(bc)
        var _9_x = (_5_x + _6_x) / 2;
        var _9_y = (_5_y + _6_y) / 2;

        var n_x = m_x + _9_x * o;
        var n_y = m_y + _9_y * o;

        var e_x = -0.5 * d_x + 2 * n_x - 0.5 * f_x;
        var e_y = -0.5 * d_y + 2 * n_y - 0.5 * f_y;

        var _10_x = e_x - d_x;
        var _10_y = e_y - d_y;
        var _11 = Math.sqrt(_10_x * _10_x + _10_y * _10_y);
        var de_x = _10_x / _11;
        var de_y = _10_y / _11;

        var _12_x = f_x - e_x;
        var _12_y = f_y - e_y;
        var _13 = Math.sqrt(_12_x * _12_x + _12_y * _12_y);
        var ef_x = _12_x / _13;
        var ef_y = _12_y / _13;

        var _14_x = ef_x - bc_x;
        var _14_y = ef_y - bc_y;

        var _15_x = de_x - ab_x;
        var _15_y = de_y - ab_y;

        var error = Math.sqrt(_14_x * _14_x + _14_y * _14_y) +
                    Math.sqrt(_15_x * _15_x + _15_y * _15_y);
        if (error < 1000) /* TODO find the right magic number */
          output.push(d_x, d_y, e_x, e_y, f_x, f_y);
        else
          input.unshift(a_x, a_y, _7_x, _7_y, m_x, m_y,
                        m_x, m_y, _8_x, _8_y, c_x, c_y);
      }
      downstream(output);
    };
  };
};

gezira.StrokeOutlineReverse = function(o) {
  return function(downstream) {
    return function(input) {
      var _1 = function(downstream) {
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
      with (gezira) { with (nile) {
        pipeline(_1, StrokeOutline, downstream)(input);
      } }
    };
  };
};

gezira.Stroke = function(o, j, c) {
  return function(downstream) {
    return function(input) {
      with (gezira) { with (nile) {
        pipeline(
          Mix(StrokeOutline(o), StrokeOutlineReverse(o), j(o), c(o)),
          downstream)(input);
      } }
    };
  };
};

/* postlude.nl */

gezira.FillBetweenEdges = function(_x) {
  return function(downstream) {
    return function(input) {
      var output = [];
      var x_, x = _x;
      var local_, local = 0;
      var run_, run = 0;
      while (input.length) {
        var x_ = input.shift();
        var y = input.shift();
        var w = input.shift();
        var h = input.shift();
        var n = x_ - x;
        if (n == 0) {
          local_ = local + w * h;
          run_ = run + h;
        } else {
          var _1 = Math.abs(local);
          var _2 = _1 < 1 ? _1 : 1;
          output.push(_2);
          var _3 = Math.abs(run);
          var _4 = _3 < 1 ? _3 : 1;
          for (var i = 0; i < (n - 1); i++)
            output.push(_4);
          local_ = run + w * h;
          run_ = run + h;
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

gezira.Render = function(s, c) {
  return function(input) {
    with (gezira) { with (nile) {
      var _1 = function(input) {
        var p_x = input[0];
        var p_y = input[1];
        pipeline(FillBetweenEdges(p_x),
                 Interleave(s(p_x + 0.5, p_y + 0.5), 4, Id, 1),
                 c(p_x + 0.5, p_y + 0.5))(input);
      };
      pipeline(GroupBy(1, 4), SortBy(0, 4), _1)(input);
    } }
  };
};

gezira.CompositeSamplers = function(s1, s2, c) {
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        with (gezira) { with (nile) {
          pipeline(Interleave(s1(start_x, start_y), 4, s2(start_x, start_y), 4),
                   c, downstream)(input);
        } }
      };
    };
  };
};

gezira.UniformColor = function(c_a, c_r, c_g, c_b) {
  return function(start_x, start_y) {
    return function(downstream) {
      return function(input) {
        var output = [];
        while (input.length) {
          var _ = input.shift();
          output.push(c_a, c_r * c_a, c_g * c_a, c_b * c_a);
        }
        downstream(output);
      };
    };
  };
};
