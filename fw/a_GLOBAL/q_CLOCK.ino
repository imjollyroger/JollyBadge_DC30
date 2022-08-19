/*

  CLOCK

*/

void switchMCUState(MCUState state) {
  switch (state) {
    case fast: {
      GCLK->GENDIV.reg = GCLK_GENDIV_DIV(1) | GCLK_GENDIV_ID(0);
      break;
    }  
    case slow: {
      GCLK->GENDIV.reg = GCLK_GENDIV_DIV(CLOCK_DIVIDER) | GCLK_GENDIV_ID(0);
      break;  
    }
  }
}
