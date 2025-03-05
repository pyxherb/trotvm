# Importing in XY

## Importing Order

The compiler will import the unconditional imports first, and then import the
conditional imports in declaration order.

For example:

```xy
import a;
import c if (@a.d())
import b;
```

Will import `a` and `b` first, and then import c if `@a.d()` is true.
