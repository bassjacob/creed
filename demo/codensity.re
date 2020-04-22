/* The codensity transform using the Higher library.

      From Section 2.3 of

         Lightweight Higher-Kinded Polymorphism
         Jeremy Yallop and Leo White
         Functional and Logic Programming 2014
   */
open Higher; /* class Monad */

class virtual monad ('m) = {
  as _;
  pub virtual return: 'a .'a => app('a, 'm);
  pub virtual bind: 'a 'b .(app('a, 'm), 'a => app('b, 'm)) => app('b, 'm);
}; /* class Functor */

class virtual functor_ ('f) = {
  as _;
  pub virtual fmap: 'a 'b .('a => 'b, app('a, 'f)) => app('b, 'f);
}; /* class (Functor f, Monad m) => Freelike f m */

class virtual freelike ('f, 'm) (pf: functor_('f), mm: monad('m)) = {
  as _;
  pub pf: functor_('f) = pf;
  pub mm: monad('m) = mm;
  pub virtual wrap: 'a .app(app('a, 'm), 'f) => app('a, 'm);
}; /* newtype C m a = C { forall b. (a -> m b) -> m b } */

type c('a, 'm) = {c: 'b .('a => app('b, 'm)) => app('b, 'm)};

module C =
  Newtype2(
    {
      type t('a, 'm) = c('a, 'm);
    }
  ); /* instance Monad (C m) */

let monad_c = () => {
  as _;
  inherit class monad(app('m, C.t));
  pub return = (a) => C.inj({c: (h) => h(a)});
  pub bind = {
    let bind = ({c: p}, k) => {c: (h) => p((a) => k(a).c(h))};
    (m, k) => C.inj(bind(C.prj(m), (a) => C.prj(k(a))));
  }
}; /* rep :: Monad m => m a -> C m a */

let rep: 'a 'm .(#monad('m), app('a, 'm)) => c('a, 'm) =
  (o, m) => {c: (k) => o#bind(m, k)}; /* abs :: Monad m => C m a -> m a */

let abs: 'a 'm .(#monad('m), c('a, 'm)) => app('a, 'm) =
  (o, c) => c.c(o#return); /* data Free = Return a | Wrap (f (Free f a)) */

type free('a, 'f) =
  | Return('a)
  | Wrap(app(free('a, 'f), 'f));

module Free =
  Newtype2(
    {
      type t('a, 'f) = free('a, 'f);
    }
  ); /* instance Functor f => Monad (Free f) */

let monad_free = (functor_free: #functor_('f)) => {
  as _;
  inherit class monad(app('f, Free.t));
  pub return = (v) => Free.inj(Return(v));
  pub bind = {
    let rec bind = (m, k) =>
      switch m {
      | Return(a) => k(a)
      | Wrap(t) => Wrap(functor_free#fmap((m) => bind(m, k), t))
      };
    (m, k) => Free.inj(bind(Free.prj(m), (a) => Free.prj(k(a))));
  }
}; /* instance Functor f => FreeLike (Free f) */

let freelike_free = (ff: #functor_('f)) => {
  as _;
  inherit
    (class freelike('f, app('f, Free.t)))(
      ff,
      monad_free(ff)
    ); /* We need the fmap to handle the conversion between ('a, 'f)
     free and the app version in the argument of Wrap */
  pub wrap = (x) => Free.inj(Wrap(ff#fmap(Free.prj, x)))
}; /* instance FreeLike f m => FreeLike f (C m) */

let freelike_c = (f_functor: #functor_('f), freelike: #freelike('f, 'm)) => {
  as _;
  inherit (class freelike('f, app('m, C.t)))(f_functor, monad_c());
  pub wrap = (t) => C.inj({c: (h) => freelike#wrap(f_functor#fmap((p) => C.prj(p).c(h), t))})
};

type freelike_poly('a, 'f) = {
  fl: 'm 'd .(#freelike('f, 'm) as 'd) => app('a, 'm)
}; /* improve :: Functor f => (forall m. FreeLike f m => m a) -> Free f a */

let improve: 'a 'f .(#functor_('f), freelike_poly('a, 'f)) => free('a, 'f) =
  (d, {fl}) =>
    Free.prj(
      abs(monad_free(d), C.prj(fl(freelike_c(d, freelike_free(d)))))
    ); /* data F_IO b = GetChar (Char -> b) | PutChar Char b */

type f_io('b) =
  | GetChar(char => 'b)
  | PutChar(char, 'b);

module F_io =
  Newtype1(
    {
      type t('b) = f_io('b);
    }
  ); /* instance Functor F_IO */

let functor_f_io = {
  as _;
  inherit class functor_(F_io.t);
  pub fmap = (h, l) =>
    F_io.inj(
      switch (F_io.prj(l)) {
      | GetChar(f) => GetChar(((x) => h(f(x))))
      | [@implicit_arity] PutChar(c, x) => [@implicit_arity] PutChar(c, h(x))
      }
    )
}; /* getChar :: FreeLike F_IO m => m Char */

let getChar: 'm .#freelike(F_io.t, 'm) => app(char, 'm) =
  (f) => f#wrap(F_io.inj(GetChar(f#mm#return))); /* putChar :: FreeLike F_IO m => Char -> m () */

let putChar: 'm .(#freelike(F_io.t, 'm), char) => app(unit, 'm) =
  (f, c) =>
    f#wrap(
      F_io.inj([@implicit_arity] PutChar(c, f#mm#return()))
    ); /* revEcho :: FreeLike F_IO m => m () */

let rec revEcho: 'm .#freelike(F_io.t, 'm) => app(unit, 'm) =
  (f) => {
    let (>>=) = (c) => f#mm#bind(c);
    getChar(f)
    >>= (
      (c) =>
        if (c != ' ') {
          revEcho(f) >>= (() => putChar(f, c));
        } else {
          f#mm#return();
        }
    );
  }; /* data Output a = Read (Output a) | Print Char (Output a) | Finish a */

type output('a) =
  | Read(output('a))
  | Print(char, output('a))
  | Finish('a); /* run :: Free F_IO a -> Stream Char -> Output a */
  
let rec run: 'a .(free('a, F_io.t), list(char)) => output('a) =
  (f, cs) =>
    switch f {
    | Return(a) => Finish(a)
    | Wrap(x) =>
      switch (F_io.prj(x)) {
      | GetChar(f) => Read(run(f(Belt.List.headExn(cs)), Belt.List.tailExn(cs)))
      | [@implicit_arity] PutChar(c, p) => [@implicit_arity] Print(c, run(p, cs))
      }
    }; /* run revEcho stream */

let simulate_original = (stream) =>
  run(Free.prj(revEcho(freelike_free(functor_f_io))), stream); /* run (improve revEcho) stream */

let simulate_improved = (stream) => run(improve(functor_f_io, {fl: (d) => revEcho(d)}), stream);