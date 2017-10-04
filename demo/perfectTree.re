open Higher;

type perfect 'a =
  | Zero 'a
  | Succ (perfect ('a, 'a));

type perfect_folder 'f = {
  zero: 'a .'a => app 'a 'f,
  succ: 'a .app ('a, 'a) 'f => app 'a 'f
};

let rec foldp: 'f 'a .perfect_folder 'f => perfect 'a => app 'a 'f =
  fun {zero, succ} =>
    fun
    | Zero l => zero l
    | Succ p => succ (foldp {zero, succ} p);

module Perfect =
  Newtype1 {
    type t 'a = perfect 'a;
  };

let idp p =>
  Perfect.(prj (foldp {zero: fun l => inj (Zero l), succ: fun b => inj (Succ (prj b))} p));
