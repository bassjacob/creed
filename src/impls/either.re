open Higher;

open Functor;

type e 'a 'b =
  | Right 'a
  | Left 'b;

module E =
  Newtype2 {
    type t 'a 'b = e 'a 'b;
  };

let functor_e () => {
  as _;
  inherit class functor_ _;
  pub fmap: 'a 'b .('a => 'b) => app 'a _ => app 'b _ =
    fun (type a b) => (
      fun f e =>
        switch (E.prj e) {
        | Right x => E.inj @@ Right (f x)
        | Left y => E.inj @@ Left y
        }:
        (a => b) => app a _ => app b _
    )
};
