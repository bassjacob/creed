open Higher;

open Functor;

class virtual applicative_ ('f) (f: functor_('f)) = {
  as self;
  pub virtual pure: 'a .'a => app('a, 'f);
  pub virtual apply: 'a 'b .(app('a => 'b, 'f), app('a, 'f)) => app('b, 'f);
  pub liftA2: 'a 'b 'c .(('a, 'b) => 'c, app('a, 'f), app('b, 'f)) => app('c, 'f) =
    (g, a1, a2) => self#apply(f#fmap(g, a1), a2);
};