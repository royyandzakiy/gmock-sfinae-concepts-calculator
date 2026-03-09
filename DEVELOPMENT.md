- add pytest

progress:
- solved issue of failing to detect tests using gtest with msvc
	- solution: use gtest instead of gtest_main. manually add main