/* open Higher; */

/* let foldMap (m: monoid_ 'm) (f: foldable_ 'f) g fo => f#foldr (fun a b => m#mappend (g m a) b) m#mempty fo; */

/* let m = (monoid_l ()); */
/* Js.log @@ foldMap m (foldable_l ()) (fun m a => m#mappend (L.inj @@ Cons a Null) m#mempty) (L.inj @@ Cons 2 Null); */

/* /1* Js.log @@ foldMap (monoid_l ()) (foldable_l ()) (fun m (_: int) => m#mempty) (L.inj @@ Cons 1 Null); *1/ */

/* /1* let foo: type f a b. functor_ f => (a => b) => app a f => app b f = fun f g a => f#fmap g a; *1/ */

/* /1* Js.log @@ foo (functor_e ()) (fun x => x + 1) (E.inj (Right 1)); *1/ */
