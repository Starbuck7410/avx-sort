# avx-sort
This repo serves dual-purpose: It's both a test to see if I can write a sorting algorithm which takes advanteage of SIMD instructions, and to see whether I can use CMake and GitHub actions to generate Visual Studio build files.

## Goals

- Write and benchmark a SIMD-optimized sorting algorithm in C  
- Learn to configure and use CMake for portable builds  
- Use GitHub Actions to automate Visual Studio project generation

## Achievements

- Proven that using AVX is faster (even on a slow bubble sort)
- The GitHub actions workflow works! I just need to hope these files will also be backwards compatible with VS 2017
- Leared why everybody HATES CMake with a passion
- Had fun? This was pretty fun i won't lie
