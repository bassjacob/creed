open Higher;

open Functor;

type o 'a = option 'a;

module O =
  Newtype1 {
    type t 'a = o 'a;
  };

let functor_o = {
  as _;
  inherit class functor_ O.t;
  pub fmap g o =>
    O.inj (
      switch (O.prj o) {
      | None => None
      | Some x => Some (g x)
      }
    )
};
