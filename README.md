# ultrie

[![Build Status](https://travis-ci.com/xmidt-org/ultrie.svg?branch=master)](https://travis-ci.com/xmidt-org/ultrie)
[![codecov.io](http://codecov.io/github/xmidt-org/ultrie/coverage.svg?branch=master)](http://codecov.io/github/xmidt-org/ultrie?branch=master)
[![Coverity](https://img.shields.io/coverity/scan/16677.svg)](https://scan.coverity.com/projects/ultrie)
[![Apache V2 License](http://img.shields.io/badge/license-Apache%20V2-blue.svg)](https://github.com/xmidt-org/ultrie/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/xmidt-org/ultrie.svg)](CHANGELOG.md)


A powerful C based trie library and set of utilities that allow you to build highly
efficient tries dynamically and serialize them into a directly usable format.

# Building and Testing Instructions

```
mkdir build
cd build
cmake ..
make
make test
```

# Dedication

Years ago, I was fortunate enough to work with Edwin (Ed) Rose.  He shared an
implementation of this trie with me for a project we worked on together.  His
concept for how to dehydrate the trie into an array of bytes and use the array
in place without rehydration was both inspiring as well as highly powerful.

Unfortunately Ed passed away in 2010 and I've not been able to debug the original
code completely.  This new implementation is dedicated to the great design and
idea that Ed came up with in the 1980s.  Thank you Ed.

 - Weston Schmidt
