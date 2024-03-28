#ifndef _IIR_FILTER
#define _IIR_FILTER

typedef struct {
    float alpha;
    float output;
}IIRFilter;

void IIRFilterInit(IIRFilter * iir, float alpha);
float IIRFilterUpdate(IIRFilter * iir, float input);

#endif