#include <stdio.h>
char letter(char a, char b, char c){

    if(a == 'A'){
        if(b == 'A'){
            if(c =='A' || c =='G'){return 'f';}
            else{return 'l';}
        }
        if(b == 'T'){
            if(c =='A' || c =='G'){return 'y';}
            else{return '.';}
        }
        if(b == 'G'){return 's';}
        if(b == 'C'){
            if(c =='A' || c =='G'){return 'c';}
            if(c == 'T'){return '.';}
            if(c == 'C'){return 'w';}
        }
    }
    if(a == 'G'){
        if(b == 'A'){return 'l';}
        if(b == 'G'){return 'p';}
        if(b == 'T'){
            if(c == 'A' || c == 'G'){return 'h';}
            else{return 'q';}
        }
        if(b == 'C'){return 'r';}

    }
    if(a == 'T'){
       if(b == 'A'){
           if(c =='C'){return 'm';}
            else{return 'i';}
       }
       if(b == 'G'){return 't';}
       if(b == 'T'){
            if(c =='A' || c =='G'){return 'n';}
            else{return 'k';}
       }
       if(b == 'C'){
           if(c =='A' || c =='G'){return 's';}
            else{return 'r';}
       }
    }
    if(a == 'C'){
        if(b == 'A'){return 'v';}
        if(b == 'G'){return 'a';}
        if(b == 'T'){
            if(c =='A' || c =='G'){return 'd';}
            else{return 'e';}
        }
        if(b == 'C'){return 'g';}
    }
}

int main() {

    int i,j,k,v,t;
    char a = 'a';
    int introns[4] = {0,0,0,0};
    char dna[3000];
    int dna_length = 0;
    char amino[2900];
    int amino_length = 0;
    char dna_coded[3000];
    int FEL = 0;
    int TEL = 0;
    int SEL = 0;

   while(a != '.'){
       scanf("%c",&a);
       if(a == '\n' || a == ' '|| a == '\t' ){continue;}
       else{   if(a != '.') { dna[dna_length] = a; dna_length++;} }
   }
   a = 'a';
   while(a != '.'){
       scanf("%c",&a);
       if(a == '\n' || a == ' '|| a == '\t' ){continue;}
       else{   if(a != '.') { amino[amino_length] = a; amino_length++;}}
   }

   for(i = 0;i<dna_length;i+=3){
        if( letter(dna[i],dna[i+1],dna[i+2]) == amino[i/3])FEL++;
        else break;
    }
   for(i = 1;i<=amino_length;i++){
        if(letter(dna[dna_length-3*(i+1)],dna[dna_length-3*(i+1)+1],dna[dna_length-3*(i+1)+2]) == amino[ amino_length - i]) TEL++;
        else break;
    }


    for (i = (FEL)*3; i<dna_length - (TEL+2)*3; i++)
        {
            SEL = 0;
            if(letter(dna[i],dna[i+1],dna[i+2]) == amino[FEL])
                {
                    for (j = 0; j<+amino_length-TEL-FEL;j++)
                        {
                            if(amino[FEL+j] != letter(dna[i + 3*j],dna[i+3*j + 1],dna[i+3*j + 2])){break;}
                            SEL++;
                        }
                    if (SEL ==  amino_length-FEL-TEL)
                        {
                            introns[0] = FEL*3;
                            introns[1] = i-1;
                            introns[2] = i+ SEL*3 ;
                            introns[3] = dna_length - 3*(TEL+1) -1;
                            break;
                        }
                }
        }

if(FEL*SEL*TEL == 0 || FEL+SEL+TEL != amino_length)
{
    FEL++;
    for (v = 0; v< FEL ;v++)
        {
            FEL--;
            TEL = 1;
            for(t = 1;t<amino_length;t++)
                {   
                    if(letter(dna[dna_length-3*(t+1) ],dna[dna_length-3*(t+1) +1 ],dna[dna_length-3*(t+1)+2]) == amino[ amino_length - t])
                        {
                            TEL++;
                            for(i = FEL*3+1; i< dna_length -3*(TEL+1); i++)
                                {
                                    SEL = 0;
                                    while(letter(dna[i+3*SEL],dna[i+ 3*SEL+1],dna[i+3*SEL+2]) == amino[FEL])
                                        {
                                            SEL++;
                                            if(SEL+FEL+TEL == amino_length )
                                                {
                                                    introns[0] = FEL*3;
                                                    introns[1] = i -1;
                                                    introns[2] = introns[1]+(SEL*3)+1;
                                                    introns[3] = dna_length - 3*(TEL+1)-1;
                                                    break;
                                                }
                                        }
                                        
                                    if(SEL+FEL+TEL == amino_length){break;}
                                }
                            if(SEL*TEL*FEL != 0 && SEL+FEL+TEL == amino_length &&  introns[1]-introns[0] >= 0 && introns[3] - introns[2]>= 0  && introns[2] - introns[1]> 0 ){break;}
                        }
                    else break;
                }
            if(SEL*TEL*FEL != 0 && SEL+FEL+TEL == amino_length &&  introns[1]-introns[0] >= 0 && introns[3] - introns[2]>= 0  && introns[2] - introns[1]> 0 ){break;}
        }
}

   if(FEL*SEL*TEL == 0|| FEL+SEL+TEL != amino_length || introns[1] -introns[0] < 0 ||introns[3] -introns[2] < 0    ){printf("NONE");}
   else{printf("%d %d %d %d",introns[0],introns[1],introns[2],introns[3]);}

    return 0;
}