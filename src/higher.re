/* Representation of type application.  This corresponds to the "apply"
   variant type in a defunctionalized program.  Application is postfix. */
type app 'p 'f;

module type Newtype0 = {
  type s;
  type t;
  external inj : s => t = "%identity";
  external prj : t => s = "%identity";
};

module type Newtype1 = {
  type s 'a;
  type t;
  external inj : s 'a => app 'a t = "%identity";
  external prj : app 'a t => s 'a = "%identity";
};

module type Newtype2 = {
  type s 'a 'b;
  type t;
  external inj : s 'a 'b => app 'a (app 'b t) = "%identity";
  external prj : app 'a (app 'b t) => s 'a 'b = "%identity";
};

module type Newtype3 = {
  type s 'a 'b 'c;
  type t;
  external inj : s 'a 'b 'c => app 'a (app 'b (app 'c t)) = "%identity";
  external prj : app 'a (app 'b (app 'c t)) => s 'a 'b 'c = "%identity";
};

module type Newtype4 = {
  type s 'a 'b 'c 'd;
  type t;
  external inj : s 'a 'b 'c 'd => app 'a (app 'b (app 'c (app 'd t))) = "%identity";
  external prj : app 'a (app 'b (app 'c (app 'd t))) => s 'a 'b 'c 'd = "%identity";
};

module type Newtype5 = {
  type s 'a 'b 'c 'd 'e;
  type t;
  external inj : s 'a 'b 'c 'd 'e => app 'a (app 'b (app 'c (app 'd (app 'e t)))) = "%identity";
  external prj : app 'a (app 'b (app 'c (app 'd (app 'e t)))) => s 'a 'b 'c 'd 'e = "%identity";
};

module type Newtype6 = {
  type s 'a 'b 'c 'd 'e 'f;
  type t;
  external inj : s 'a 'b 'c 'd 'e 'f => app 'a (app 'b (app 'c (app 'd (app 'e (app 'f t))))) =
    "%identity";
  external prj : app 'a (app 'b (app 'c (app 'd (app 'e (app 'f t))))) => s 'a 'b 'c 'd 'e 'f =
    "%identity";
};

module Common = {
  type t;
  external inj : 'a => 'b = "%identity";
  external prj : 'a => 'b = "%identity";
};

module Newtype0 (T: {type t;}) => {
  type s = T.t;
  include Common;
};

module Newtype1 (T: {type t 'a;}) => {
  type s 'a = T.t 'a;
  include Common;
};

module Newtype2 (T: {type t 'a 'b;}) => {
  type s 'a 'b = T.t 'a 'b;
  include Common;
};

module Newtype3 (T: {type t 'a 'b 'c;}) => {
  type s 'a 'b 'c = T.t 'a 'b 'c;
  include Common;
};

module Newtype4 (T: {type t 'a 'b 'c 'd;}) => {
  type s 'a 'b 'c 'd = T.t 'a 'b 'c 'd;
  include Common;
};

module Newtype5 (T: {type t 'a 'b 'c 'd 'e;}) => {
  type s 'a 'b 'c 'd 'e = T.t 'a 'b 'c 'd 'e;
  include Common;
};

module Newtype6 (T: {type t 'a 'b 'c 'd 'e 'f;}) => {
  type s 'a 'b 'c 'd 'e 'f = T.t 'a 'b 'c 'd 'e 'f;
  include Common;
};
