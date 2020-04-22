open Higher;

class virtual functor_ ('f) = {
  as self; /* minimal interface */
  pub virtual fmap: 'a 'b .('a => 'b, app('a, 'f)) => app('b, 'f); /* overridable */
  pub virtual leftFmap: 'a 'b .('a, app('b, 'f)) => app('a, 'f);
  pub leftFmap = (a) => self#fmap((_) => a);
};