/* An example of typed defunctionalization.

      From Section 1.2 of

         Lightweight Higher-Kinded Polymorphism
         Jeremy Yallop and Leo White
         Functional and Logic Programming 2014
   */
/*** A higher-order program: folds over lists, together with functions
     defined using folds. */
module Original = {
  let rec fold: type a b. ((((a, b)) => b, b, list(a))) => b =
    ((f, u, l)) =>
      switch l {
      | [] => u
      | [x, ...xs] => f((x, fold((f, u, xs))))
      };
  let sum = (l) => fold((((x, y)) => x + y, 0, l));
  let add = ((n, l)) => fold((((x, l')) => [x + n, ...l'], [], l));
}; /*** The higher-order program in defunctionalized form. */

module Defunctionalized = {
  type arrow(_, _) =
    | Fn_plus: arrow((int, int), int)
    | Fn_plus_cons(int): arrow((int, list(int)), list(int));
  let apply: type a b. ((arrow(a, b), a)) => b =
    ((appl, v)) =>
      switch appl {
      | Fn_plus =>
        let (x, y) = v;
        x + y;
      | Fn_plus_cons(n) =>
        let (x, l') = v;
        [x + n, ...l'];
      };
  let rec fold: type a b. ((arrow((a, b), b), b, list(a))) => b =
    ((f, u, l)) =>
      switch l {
      | [] => u
      | [x, ...xs]=> apply((f, (x, fold((f, u, xs)))))
      };
  let sum = (l) => fold((Fn_plus, 0, l));
  let add = ((n, l)) => fold((Fn_plus_cons(n), [], l));
};