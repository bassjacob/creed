/* Kind polymorphism using the Higher library.

      From Section 2.4 of

         Lightweight Higher-Kinded Polymorphism
         Jeremy Yallop and Leo White
         Functional and Logic Programming 2014
   */
open Higher;

let id x => x;

class virtual category 'f = {
  as _;
  pub virtual ident: 'a .app 'a (app 'a 'f);
  pub virtual compose: 'a 'b 'c .app 'b (app 'a 'f) => app 'c (app 'b 'f) => app 'c (app 'a 'f);
};

module Fun =
  Newtype2 {
    type t 'a 'b = 'b => 'a;
  };

let category_fun = {
  as _;
  inherit class category Fun.t;
  pub ident = Fun.inj id;
  pub compose f g => Fun.inj (fun x => Fun.prj g (Fun.prj f x))
};

type ip 'n 'm = {ip: 'a .app 'a 'm => app 'a 'n};

module Ip =
  Newtype2 {
    type t 'n 'm = ip 'n 'm;
  };

let category_ip = {
  as _;
  inherit class category Ip.t;
  pub ident = Ip.inj {ip: id};
  pub compose f g => Ip.inj {ip: fun x => (Ip.prj g).ip ((Ip.prj f).ip x)}
};

/* The type of category computations in left-associative form.  All
      values are of the form

         Compose (Compose(...(Ident, c1), c2), ... cn)
   */
type cat_left 'b 'a 'f =
  | Ident :cat_left 'a 'a 'f
  | Compose (cat_left 'b 'a 'f) (app 'c (app 'b 'f)) :cat_left 'c 'a 'f;

module CL =
  Newtype3 {
    type t 'b 'a 'f = cat_left 'b 'a 'f;
  };

/* An instance of category that puts computations into normal form. */
let category_cat_left (_: #category 'f) => {
  as self;
  inherit class category (app 'f CL.t);
  pub ident = CL.inj Ident;
  pub compose:
    'a 'b 'c .
    app 'b (app 'a (app 'f CL.t)) => app 'c (app 'b (app 'f CL.t)) => app 'c (app 'a (app 'f CL.t))
   =
    fun (type a b c) => (
      fun (type a b c) (f: app b (app a (app 'f CL.t))) (j: app c (app b (app 'f CL.t))) =>
        CL.(
          switch (prj j: cat_left c b 'f) {
          | Ident => (f: app c (app a (app 'f CL.t)))
          | Compose g h [@implicit_arity] =>
            inj (Compose (prj (self#compose f (inj g))) h [@implicit_arity])
          }
        ):
        app b (app a (app 'f CL.t)) => app c (app b (app 'f CL.t)) => app c (app a (app 'f CL.t))
    )
};

/* Run a left-associative computation. */
let rec observe: type f a b. #category f => cat_left b a f => app b (app a f) =
  fun cat =>
    fun
    | Ident => cat#ident
    | Compose f g [@implicit_arity] => cat#compose (observe cat f) g;

/* Lift a value into cat_left. */
let promote: type f a b. app b (app a f) => cat_left b a f =
  fun c => Compose Ident c [@implicit_arity];
