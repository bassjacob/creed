/* Leibniz equality using the Higher library.

      From Section 2.2 of

         Lightweight Higher-Kinded Polymorphism
         Jeremy Yallop and Leo White
         Functional and Logic Programming 2014
   */
open Higher;

module Leibniz: {
  module Eq: Newtype2;
  type eq('a, 'b) =
    app(
      'b,
      app('a, Eq.t)
    ); /*** A value of type [(a, b) eq] is a proof that the types [a] and [b] are
      equal. */
  let refl:
    unit => eq('a, 'a); /*** Equality is reflexive: [refl ()] builds a proof that any type [a] is
      equal to itself. */
  let subst:
    (eq('a, 'b), app('a, 'f)) => app('b, 'f); /*** If types [a] and [b] are equal then they are interchangeable in any
      context [f]. */
  let trans:
    (eq('a, 'b), eq('b, 'c)) => eq('a, 'c); /*** Equality is transitive: if [a] and [b] are equal and [b] and [c] are
      equal then [a] and [c] are equal. */
  let symm:
    eq('a, 'b) => eq('b, 'a); /*** Equality is symmetric: if [a] and [b] are equal then [b] and [a] are
      equal */
  let cast:
    (eq('a, 'b), 'a) => 'b; /*** If types [a] and [b] are equal then we can coerce a value of type [a] to
      a value of type [b]. */
} = {
  module Id =
    Newtype1(
      {
        type t('a) = 'a;
      }
    );
  type eqaux('a, 'b) = {
    eqaux: 'f .app('a, 'f) => app('b, 'f)
  }; /*** The proof of equality of types [a] and [b] is implemented as a coercion
      from [a] to [b] in an arbitrary context [f]. */
  module Eq =
    Newtype2(
      {
        type t('b, 'a) = eqaux('a, 'b);
      }
    );
  type eq('a, 'b) = app('b, app('a, Eq.t));
  let refl = () => Eq.inj({eqaux: (x) => x});
  let subst = (ab, ctxt) => Eq.prj(ab).eqaux(ctxt);
  let trans = (ab, bc) => subst(bc, ab);
  let cast = (eq, x) => Id.prj(subst(eq, Id.inj(x)));
  let symm = (type a, eq) => {
    module S =
      Newtype1(
        {
          type t('a) = eq('a, a);
        }
      );
    S.prj(subst(eq, S.inj(refl())));
  };
};