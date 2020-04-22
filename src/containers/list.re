open Higher;

open Monoid;

open Foldable;

open Functor;

module L =
  Newtype1(
    {
      type t('a) = list('a);
    }
  );
let monoid_list =() => {
  as self;
  inherit class monoid_(L.t);
  pub mempty = L.inj([]);
  pub mappend = (l1, l2) =>
    switch (L.prj(l1), L.prj(l2)) {
    | ([], []) => self#mempty
    | ([], _) => l2
    | (_, []) => l1
    | ([v1, ...l1'], _) => L.inj @@ [v1, ...L.prj @@ self#mappend(L.inj(l1'), l2)]
    }
};


let foldable_list = () => {
  as self;
  inherit class foldable_(L.t);
  pub foldr = (f, b, l) =>
    switch (L.prj(l)) {
    | [] => b
    | [x, ...xs] => self#foldr(f, f(x, b), L.inj(xs))
    }
};

let functor_l = {
  as self;
  inherit class functor_(L.t);
  pub fmap = (g, l) =>
    L.inj(
      switch (L.prj(l)) {
      | [] => []
      | [x, ...xs] => [g(x), ...L.prj @@ self#fmap(g, L.inj(xs))]
      }
    )
};