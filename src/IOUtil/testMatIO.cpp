extern "C"{
#include "matio.h"
}

int main(int argc,char **argv)
{
    mat_t *matfp;

    matfp = Mat_Open(argv[1],MAT_ACC_RDONLY);
    if ( NULL == matfp ) {
        fprintf(stderr,"Error opening MAT file %s\n",argv[1]);
        return EXIT_FAILURE;
    }

    matvar_t * matvar;
    matvar = Mat_VarRead(matfp,"dtmp");
//    matvar = Mat_VarReadInfo(matfp,"detector");
    if(NULL!=matvar){
    	printf("read in\n");
    	matvar_t* opts = Mat_VarGetStructFieldByName(matvar,"opts",0);
    	if(opts!=NULL){
    		Mat_VarPrint(opts,1);
//    		Mat_VarFree(field);
    	}
    	matvar_t* cls = Mat_VarGetStructFieldByName(matvar,"cls",0);
    	if(cls!=NULL){
    		Mat_VarPrint(cls,1);
    	}
    	matvar_t* info = Mat_VarGetStructFieldByName(matvar,"info",0);
    	if(info!=NULL){
    		Mat_VarPrint(info,1);
    	}
    	Mat_VarFree(matvar);
    }
    else{
    	printf("detector content is null\n");
    }
    Mat_Close(matfp);
    return EXIT_SUCCESS;
}
