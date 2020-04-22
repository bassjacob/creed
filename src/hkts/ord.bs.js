// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var CamlinternalOO = require("bs-platform/lib/js/camlinternalOO.js");

function ord__001($$class) {
  var ids = CamlinternalOO.get_method_labels($$class, [
        "min",
        "max",
        "lessThanOrEqual",
        "lessThan",
        "greaterThanOrEqual",
        "greaterThan",
        "compare"
      ]);
  var min = ids[0];
  var max = ids[1];
  var lessThanOrEqual = ids[2];
  var lessThan = ids[3];
  var greaterThanOrEqual = ids[4];
  var greaterThan = ids[5];
  var compare = ids[6];
  CamlinternalOO.set_methods($$class, [
        lessThan,
        (function (self$1, a, b) {
            return /* LT */0 === Curry._3(self$1[0][compare], self$1, a, b);
          }),
        lessThanOrEqual,
        (function (self$1, a, b) {
            var match = Curry._3(self$1[0][compare], self$1, a, b);
            return match < 2;
          }),
        greaterThan,
        (function (self$1, a, b) {
            return /* GT */2 === Curry._3(self$1[0][compare], self$1, a, b);
          }),
        greaterThanOrEqual,
        (function (self$1, a, b) {
            var match = Curry._3(self$1[0][compare], self$1, a, b);
            return match !== 0;
          }),
        max,
        (function (self$1, a, b) {
            if (Curry._3(self$1[0][compare], self$1, a, b) === /* LT */0) {
              return b;
            } else {
              return a;
            }
          }),
        min,
        (function (self$1, a, b) {
            if (Curry._3(self$1[0][compare], self$1, a, b) === /* LT */0) {
              return a;
            } else {
              return b;
            }
          })
      ]);
  return (function (env, self) {
      return CamlinternalOO.create_object_opt(self, $$class);
    });
}

var ord_ = /* class */[
  undefined,
  ord__001,
  undefined,
  undefined
];

exports.ord_ = ord_;
/* No side effect */