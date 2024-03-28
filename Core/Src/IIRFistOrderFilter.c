#include<IIRFirstOrderFilter.h>


void IIRFilterInit(IIRFilter * IIR, float alpha) {
    IIR->alpha = alpha;
}

float IIRFilterUpdate(IIRFilter * iir, float input) {
    iir->output = (1 - iir->alpha) * input + (iir->alpha * iir->output);
    return iir->output;
}