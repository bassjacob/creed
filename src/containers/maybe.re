open Higher;

open Functor;

open Applicative;

open Monad;

type o('a) = option('a);

module O =
  Newtype1(
    {
      type t('a) = o('a);
    }
  );

let functor_o = {
  as _;
  inherit class functor_(O.t);
  pub fmap = (g, o) =>
    O.inj(
      switch (O.prj(o)) {
      | None => None
      | Some((x)) => Some(g(x))
      }
    )
};

let applicative_o = {
  as _;
  inherit (class applicative_(O.t))(functor_o);
  pub pure = (a) => O.inj @@ Some(a);
  pub apply = (f, a) =>
    switch (O.prj(f), O.prj(a)) {
    | (None, _) => O.inj(None)
    | (_, None) => O.inj(None)
    | (Some((g)), Some((b))) => O.inj(Some(g(b)))
    }
};

let monad_o = {
  as _;
  inherit (class monad_(O.t))(applicative_o);
  pub bind = (f, m) =>
    switch (O.prj(m)) {
    | None => O.inj(None)
    | Some((x)) => f(x)
    }
};