Play PNacl with Nim lang
========================

Why port nim to Chrome's native client?
---------------------------------------
Because I would NOT like to use C++ for native programming. And nim can compile to C. More than just for fun.

How to taste it
---------------

[Setup nacl_sdk](https://developer.chrome.com/native-client/sdk/download) and set env variable `NACL_SDK_ROOT` (eg. "/usr/local/lib/nacl_sdk/pepper_42").

[Download naclports](https://code.google.com/p/naclports/wiki/HowTo_Checkout) then build and install glibc-compat pkg. 

_Note that `gclient sync` after `git checkout ...` is unnecessary otherwise it will produce errors_.

```
cd naclports/src
./make_all.sh glibc-compat
```

[Setup nim lang](http://nim-lang.org/download.html). Mac OS X users can use `brew install nim`.

Checkout and make:
```
git clone https://github.com/hackwaly/pepper-nim.git
cd pepper-nim
make
```

Then load unpacked extension with `pepper-nim` folder in `chrome://extensions/` developer mode.
Inspect the background page of `pepper-nim` then see what's console dumps. "hello" should be printed.

Todos
-----

* Nim pepper api bindings
