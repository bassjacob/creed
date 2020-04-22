open Higher;

open Applicative;

class virtual monad_ ('m) (a: applicative_('m)) = {
  as self;
  pub virtual return: 'a .'a => app('a, 'm);
  pub return = (x) => a#pure(x);
  pub virtual bind: 'a 'b .('a => app('b, 'm), app('a, 'm)) => app('b, 'm);
  pub virtual rightBind: 'a 'b .(app('a, 'm), app('b, 'm)) => app('b, 'm);
  pub rightBind = (a, b) => self#bind((_) => b, a);
};