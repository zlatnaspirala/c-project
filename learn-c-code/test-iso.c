

int main() {

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L
  /* C95 compatible source code. */
  printf("-STDC_VERSION SUPPORT: YES");
#elif defined(__STDC__)
  /* C89 compatible source code. */
  printf("-STDC: YES");
#endif

  return 0;
}
