open Higher;

open Functor;

open Applicative;

open Monad;

type e('a, 'b) =
  | Right('a)
  | Left('b);

module E =
  Newtype2(
    {
      type t('a, 'b) = e('a, 'b);
    }
  );

let functor_e = () => {
  as _;
  inherit class functor_(app('c, E.t));
  pub fmap: 'a 'b .('a => 'b, app('a, _)) => app('b, _) =
    (type a, type b) => (
      (f, e) =>
        switch (E.prj(e)) {
        | Right(x) => E.inj @@ Right(f(x))
        | Left(y) => E.inj @@ Left(y)
        }:
        (a => b, app(a, _)) => app(b, _)
    )
};

let applicative_e = () => {
  as _;
  inherit (class applicative_(app('c, E.t)))(functor_e());
  pub pure = (a) => Right(a) |> E.inj;
  pub apply = (f, a) =>
    switch (E.prj(f), E.prj(a)) {
    | (Left(x), _) => Left(x) |> E.inj
    | (_, Left(x)) => Left(x) |> E.inj
    | (Right(f'), Right(a')) => E.inj(Right(f'(a')))
    }
};

let monad_e = () => {
  as _;
  inherit (class monad_(app('c, E.t)))(applicative_e());
  pub bind = (f, m) =>
    switch (E.prj(m)) {
    | Left(x) => Left(x) |> E.inj
    | Right(x) => f(x)
    }
};