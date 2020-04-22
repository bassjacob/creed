open Higher;

class virtual monoid_ ('f) = {
  as _;
  pub virtual mempty: 'a .app('a, 'f);
  pub virtual mappend: 'a .(app('a, 'f), app('a, 'f)) => app('a, 'f);
};