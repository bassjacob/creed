/** Operations on newtypes */

/** Type expression application. */
type app('p, 'f);

/** Construct a newtype for a type constructor with no parameters. */
module type Newtype0 = {
  type s;
  type t;
  external inj : s => t = "%identity";
  external prj : t => s = "%identity";
};

module Newtype0: (T: {type t;}) => Newtype0 with type s = T.t;

/** Construct a newtype for a type constructor with one parameter. */
module type Newtype1 = {
  type s('a);
  type t;
  external inj : s('a) => app('a, t) = "%identity";
  external prj : app('a, t) => s('a) = "%identity";
};

module Newtype1: (T: {type t('a);}) => Newtype1 with type s('a) = T.t('a);

/** Construct a newtype for a type constructor with two parameters. */
module type Newtype2 = {
  type s('a, 'b);
  type t;
  external inj : s('a, 'b) => app('a, app('b, t)) = "%identity";
  external prj : app('a, app('b, t)) => s('a, 'b) = "%identity";
};

module Newtype2: (T: {type t('a, 'b);}) => Newtype2 with type s('a, 'b) = T.t('a, 'b);

/** Construct a newtype for a type constructor with three parameters. */
module type Newtype3 = {
  type s('a, 'b, 'c);
  type t;
  external inj : s('a, 'b, 'c) => app('a, app('b, app('c, t))) = "%identity";
  external prj : app('a, app('b, app('c, t))) => s('a, 'b, 'c) = "%identity";
};

module Newtype3: (T: {type t('a, 'b, 'c);}) => Newtype3 with type s('a, 'b, 'c) = T.t('a, 'b, 'c);

/** Construct a newtype for a type constructor with four parameters. */
module type Newtype4 = {
  type s('a, 'b, 'c, 'd);
  type t;
  external inj : s('a, 'b, 'c, 'd) => app('a, app('b, app('c, app('d, t)))) = "%identity";
  external prj : app('a, app('b, app('c, app('d, t)))) => s('a, 'b, 'c, 'd) = "%identity";
};

module Newtype4:
  (T: {type t('a, 'b, 'c, 'd);}) => Newtype4 with type s('a, 'b, 'c, 'd) = T.t('a, 'b, 'c, 'd);

/** Construct a newtype for a type constructor with five parameters. */
module type Newtype5 = {
  type s('a, 'b, 'c, 'd, 'e);
  type t;
  external inj : s('a, 'b, 'c, 'd, 'e) => app('a, app('b, app('c, app('d, app('e, t))))) =
    "%identity";
  external prj : app('a, app('b, app('c, app('d, app('e, t))))) => s('a, 'b, 'c, 'd, 'e) =
    "%identity";
};

module Newtype5:
  (T: {type t('a, 'b, 'c, 'd, 'e);}) =>
  Newtype5 with type s('a, 'b, 'c, 'd, 'e) = T.t('a, 'b, 'c, 'd, 'e);

/** Construct a newtype for a type constructor with six parameters. */
module type Newtype6 = {
  type s('a, 'b, 'c, 'd, 'e, 'f);
  type t;
  external inj :
    s('a, 'b, 'c, 'd, 'e, 'f) => app('a, app('b, app('c, app('d, app('e, app('f, t)))))) =
    "%identity";
  external prj :
    app('a, app('b, app('c, app('d, app('e, app('f, t)))))) => s('a, 'b, 'c, 'd, 'e, 'f) =
    "%identity";
};

module Newtype6:
  (T: {type t('a, 'b, 'c, 'd, 'e, 'f);}) =>
  Newtype6 with type s('a, 'b, 'c, 'd, 'e, 'f) = T.t('a, 'b, 'c, 'd, 'e, 'f);