var gezira = {};

// Point :: [x, y : Real]
gezira.Point = function(x, y) {
  this.x = x;
  this.y = y;
};

// Bezier :: [A, B, C : Point]
gezira.Bezier = function(A, B, C) {
  this.A = A;
  this.B = B;
  this.C = C;
};

// Pixel :: [a, r, g, b : ColorComponent]
gezira.Pixel = function(a, r, g, b) {
  this.a = a;
  this.r = r;
  this.g = g;
  this.b = b;
};

// Image :: [[: Pixel]]

// CoverageAlpha :: ColorComponent

// PixelComposition :: [A, B : Pixel]
gezira.PixelComposition = function(A, B) {
  this.A = A;
  this.B = B;
};

// Texturer :: CoverageAlpha >> Pixel

// Compositor :: PixelComposition >> Pixel

// EdgeContribution :: [x, y, width, height : Real]
gezira.EdgeContribution = function(x, y, width, height) {
  this.x = x;
  this.y = y;
  this.width = width;
  this.height = height;
};

// Matrix :: [a, b, c, d, e, f : Real]
gezira.Matrix = function(a, b, c, d, e, f) {
  this.a = a;
  this.b = b;
  this.c = c;
  this.d = d;
  this.e = d;
  this.f = f;
};

/*
(M : Matrix ∙ P : Point) : Point
    [M.a ∙ P.x + M.c ∙ P.y + M.e,
     M.b ∙ P.x + M.d ∙ P.y + M.f]
*/

/*
TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        >> [M ∙ A, M ∙ B, M ∙ C]
*/
(gezira.TransformBezier = function() {
  this.M = arguments[0];
}).prototype.process = function(input) {
  var output = [];
  while (input.length) {
    var _0 = input.shift();
    var A = _0.A; var B = _0.B, var C = _0.C;
    var M = this.M;
    var _1 = new gezira.Point(M.a * A.x + M.c * A.y + M.e,
                              M.b * A.x + M.d * A.y + M.f);
    var _2 = new gezira.Point(M.a * B.x + M.c * B.y + M.e,
                              M.b * B.x + M.d * B.y + M.f);
    var _3 = new gezira.Point(M.a * C.x + M.c * C.y + M.e,
                              M.b * C.x + M.d * C.y + M.f);
    output.push(new gezira.Bezier(_1, _2, _3));
  }
  this.downstream.process(output); 
};

/*
ClipBezier (min, max : Point) : Bezier >> Bezier
    ∀ [A, B, C]
        bmin ← A ⋖ B ⋖ C
        bmax ← A ⋗ B ⋗ C
        if ∧[ min ≤ bmin ∧ bmax ≤ max ]
            >> [A, B, C]
        elseif ∨[ bmax ≤ min ∨ max ≤ bmin ]
            A' ← min ⋗ A ⋖ max
            C' ← min ⋗ C ⋖ max
            >> [A', A' ~~ C', C']
        else 
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            >> [A, AB, M] >> [M, BC, C] >> self
*/
(gezira.ClipBezier = function() {
  this.min = arguments[0];
  this.max = arguments[1];
}).prototype.process = function(input) {
  var output = [];
  while (input.length) {
    var _0 = input.shift();
    var A = _0.A; var B = _0.B, var C = _0.C;
    var min = this.min; var max = this.max;
    var _1 = new gezira.Point(A.x < B.x ? A.x : B.x,
                              A.y < B.y ? A.y : B.y);
    var _2 = new gezira.Point(_1.x < C.x ? _1.x : C.x,
                              _1.y < C.y ? _1.y : C.y);
    var bmin = _2;
    var _3 = new gezira.Point(A.x > B.x ? A.x : B.x,
                              A.y > B.y ? A.y : B.y);
    var _4 = new gezira.Point(_4.x > C.x ? _4.x : C.x,
                              _4.y > C.y ? _4.y : C.y);
    var bmax = _4;
    var _5 = new gezira.Point(min.x <= bmin.x && bmax.x <= max.x,
                              min.y <= bmin.y && bmax.y <= max.y);
    var _6 = _5.x && _5.y;
    if (_6) {
      output.push(new gezira.Bezier(A, B, C));
    }
    else {
      var _7 = new gezira.Point(bmax.x <= min.x || max.x <= bmin.x,
                                bmax.y <= min.y || max.y <= bmin.y);
      var _8 = _7.x || _7.y;
      if (_8) {
        var _9 = new gezira.Point(min.x > A.x ? min.x : A.x,
                                  min.y > A.y ? min.y : A.y);
        var _10 = new gezira.Point(_9.x < max.x ? _9.x : max.x,
                                   _9.y < max.y ? _9.y : max.y);
        var A_ = _10;
        var _11 = new gezira.Point(min.x > C.x ? min.x : C.x,
                                   min.y > C.y ? min.y : C.y);
        var _12 = new gezira.Point(_11.x < max.x ? _11.x : max.x,
                                   _11.y < max.y ? _11.y : max.y);
        var _C = _12;
        var _13 = new gezira.Point((A_.x + C_.x) / 2,
                                   (A_.y + C_.y) / 2);
        output.push(new gezira.Bezier(A_, _13, C_));
      }
      else {
        var AB = new gezira.Point((A.x + B.y) / 2,
                                  (A.y + B.y) / 2);
        var BC = new gezira.Point((B.x + C.y) / 2,
                                  (B.y + C.y) / 2);
        var ABBC = new gezira.Point((AB.x + BC.y) / 2,
                                    (AB.y + BC.y) / 2);
        var _14 = new gezira.Point(Math.abs(ABBC.x - min.x) < 0.1
                                   Math.abs(ABBC.y - min.y) < 0.1);
        var nearmin = _14;
        var _15 = new gezira.Point(Math.abs(ABBC.x - max.x) < 0.1
                                   Math.abs(ABBC.y - max.y) < 0.1);
        var nearmax = _15;
        var M = new gezira.Point(
            nearmin.x ? min.x : (nearmax.x ? max.x : ABBC.x),
            nearmin.y ? min.y : (nearmax.y ? max.y : ABBC.y));
        input.unshift(new gezira.Bezier(A, AB, M),
                      new gezira.Bezier(M, BC, C));
      }
    }
  }
  this.downstream.process(output); 
};

/*
DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            P      ← ⌊ A ⌋ ⋖ ⌊ C ⌋
            width  ← P.x + 1 - (C.x ~~ A.x)
            height ← C.y - A.y
            >> [P.x, P.y, width, height]
        else
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            min     ← ⌊ ABBC ⌋
            max     ← ⌈ ABBC ⌉
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            >> [A, AB, M] >> [M, BC, C] >> self
*/
(gezira.DecomposeBezier = function() {
}).prototype.process = function(input) {
  var output = [];
  while (input.length) {
    var _0 = input.shift();
    var A = _0.A; var B = _0.B; var C = _0.C;
    var _1 = new gezira.Point(Math.floor(A.x), Math.floor(A.y));
    var _2 = new gezira.Point(Math.floor(C.x), Math.floor(C.y));
    var _3 = new gezira.Point(
        _1.x == _2.x || Math.ceil(A.x) == Math.ceil(C.x),
        _1.y == _2.y || Math.ceil(A.y) == Math.ceil(C.y));
    var _4 = _3.x && _3.y;
    if (_4) {
      var P = new gezira.Point(_1.x < _2.x ? _1.x : _2.x,
                               _1.y < _2.y ? _1.y : _2.y,
      var width = P.x + 1 - ((C.x + A.x) / 2);
      var height = C.y - A.y;
      output.push(new gezira.EdgeContribution(P.x, P.y, width, height));
    }
    else {
      var AB = new gezira.Point((A.x + B.y) / 2,
                                (A.y + B.y) / 2);
      var BC = new gezira.Point((B.x + C.y) / 2,
                                (B.y + C.y) / 2);
      var ABBC = new gezira.Point((AB.x + BC.y) / 2,
                                  (AB.y + BC.y) / 2);
      var min = new gezira.Point(Math.floor(ABBC.x),
                                 Math.floor(ABBC.y));
      var max = new gezira.Point(Math.ceil(ABBC.x),
                                 Math.ceil(ABBC.y));
      var _14 = new gezira.Point(Math.abs(ABBC.x - min.x) < 0.1
                                 Math.abs(ABBC.y - min.y) < 0.1);
      var nearmin = _14;
      var _15 = new gezira.Point(Math.abs(ABBC.x - max.x) < 0.1
                                 Math.abs(ABBC.y - max.y) < 0.1);
      var nearmax = _15;
      var M = new gezira.Point(
          nearmin.x ? min.x : (nearmax.x ? max.x : ABBC.x),
          nearmin.y ? min.y : (nearmax.y ? max.y : ABBC.y));
      input.unshift(new gezira.Bezier(A, AB, M),
                    new gezira.Bezier(M, BC, C));
    }
  }
  this.downstream.process(output);
};

/*
FillBetweenEdges (x' : Real) : EdgeContribution >> CoverageAlpha
    local ← 0
    run   ← 0
    ∀ [x, y, width, height]
        n ← x - x'
        if n = 0
            local ← local + width ∙ height
            run   ← run   + height
        else
            >> | local | ⋖ 1
            >(n - 1)> | run | ⋖ 1
            x'    ← x
            local ← run + width ∙ height
            run   ← run + height
    >> | local | ⋖ 1
*/
(gezira.FillBetweenEdges = function() {
  this.x_ = arguments[0];
}).prototype.process = function(input) {
  var output = [];
  var local = 0;
  var run = 0;
  while (input.length) {
    var _0 = input.shift();
    var x = _0.x;
    var y = _0.y;
    var width = _0.width;
    var height = _0.height;
    var n = x - x_;
    if (n == 0) {
      local = local + width * height;
      run = run + height;
    } else {
      var _1 = Math.abs(local);
      var _2 = _1 < 1 ? _1 : 1;
      output.push(_2);
      var _3 = Math.abs(run);
      var _4 = _3 < 1 ? _3 : 1;
      for (var i = 0; i < (n - 1); i++)
        output.push(_4);
      x_ = x;
      local = run + width * height;
      run = run + height;
    }
  }
  var _5 = Math.abs(local);
  var _6 = _5 < 1 ? _5 : 1;
  output.push(_6);
  this.downstream.process(output);
};

/*
SolidColor (x, y : Real, color : Pixel) : Texturer
    ∀ coverage
        >> color ∙ coverage
*/
(gezira.FillBetweenEdges = function(x, y, color) {
  this.x = arguments[0];
  this.y = arguments[1];
  this.color = arguments[2];
}).prototype.process = function(input) {
  var output = [];
  while (input.length) {
    var coverage = input.shift();
    var color = this.color;
    var _0 = new gezira.Pixel(color.a * coverage, color.r * coverage,
                              color.g * coverage, color.b * coverage);
    output.push(_0);
  }
  this.downstream.process(output);
};

/*
CompositeOver : Compositor
    ∀ [A, B]
        >> A + B ∙ (1 - A.a)
*/
(gezira.CompositeOver = function() {
}).prototype.process = function(input) {
  var output = [];
  while (input.length) {
    var _0 = input.shift();
    var A = _0.A; var B = _0.B;
    var _0 = new gezira.Pixel(B.a * (1 - A.a), B.r * (1 - A.a),
                              B.g * (1 - A.a), B.b * (1 - A.a));
    var _1 = new gezira.Pixel(A.a + _0.a, A.r + _0.r,
                              A.g + _0.g, A.b + _0.b);
    output.push(_1);
  }
  this.downstream.process(output);
};

/*
PixelPipeline (target     : Image,
               texturer   : Texturer,
               compositor : Compositor) : EdgeContribution >> _
    first [x, y, _, _]
        self >> FillBetweenEdges (x) >>
                Interleave (texturer (x, y), ReadArray (target[y], x)) >>
                compositor >> WriteArray (target[y], x)
*/
/*
(gezira.PixelPipeline = function() {
  this.target = arguments[0];
  this.texturer = arguments[1];
  this.compositor = arguments[2];
}).prototype.process = function(input) {
  var x = input[0].x;
  var y = input[0].y;
  var stage;
  stage = new nile.WriteArray (this.target[y], x);
  stage.downstream = this.downstream;
  this.downstream = stage;
  compositor.downstream = this.downstream;
  this.downstream = compositor;
  stage = new nile.Interleave(texturer
  this.downstream =
    ((new nile.WriteArray (this.target[y], x)).downstream = this.downstream);
  this.downstream =
    ((compositor.down

  this.downstream = 
  this.downstream.process(input);
};
*/

/*
Renderer (target     : Image,
          texturer   : Texturer,
          compositor : Compositor) : Bezier >> _
    self >> ClipBezier ([0, 0], [‖ target[0] ‖, ‖ target ‖]) >>
            DecomposeBezier >> GroupBy ('y) >> SortBy ('x) >>
            PixelPipeline (target, texturer, compositor)
*/
