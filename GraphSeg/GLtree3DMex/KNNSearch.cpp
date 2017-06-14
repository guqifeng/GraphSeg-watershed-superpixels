#include "mex.h"




#include "GLtree.cpp"
//#include "FunctionsLib.h"


// In Matlab la funzione deve essere idc=NNSearch(x,y,pk,ptrtree)

/* the gateway function */
// In matlab la funzione deve essere
//[NNG,dist]=KNNSearch(p,qp,ptrtree,k)

void mexFunction( int nlhs, mxArray *plhs[1],
int nrhs,  const mxArray *prhs[4])
{
    
    double       *p;

    double       *qp;

    Coord3D       pk;
    
    double  *ptrtree;
    double * idcdouble;
    int N,Nq,i,j;
    double* outdistances;
    
    
    
    // Errors check
    
    if(nrhs!=4)
        mexErrMsgTxt("Four inputs required.");
    
      if(nlhs>2)
    {  mexErrMsgTxt("Maximum two outputs supported");}
    
    
    
  
   
 N=mxGetN(prhs[0]);
 Nq=mxGetN(prhs[1]);//non � il numero dei query solo un uso temporaneo
 
 if(N!=3 || Nq!=3)
  { mexErrMsgTxt("Only 3D points supported ");
         } 
  
  if( !mxIsDouble(prhs[0]) || !mxIsDouble(prhs[1]))
 { mexErrMsgTxt("Inputs must be double vectors ");
         } 
    
    
    
    p = mxGetPr(prhs[0]);//puntatore all'array dei punti
   
    qp = mxGetPr(prhs[1]);//puntatore all'array dei punti query
   
    ptrtree = mxGetPr(prhs[2]);//puntatore all'albero precedentemente fornito
    double *k=mxGetPr(prhs[3]);
    
 
    
    
    
     int kint=*k;//numberof neighbours
     
     N=mxGetM(prhs[0]);//dimensione reference
     Nq=mxGetM(prhs[1]);//numero dei query 
     
     
         if (*k>N)
  {
      mexErrMsgTxt("Can not run search reference points are less than k");
         }
    
    plhs[0] = mxCreateDoubleMatrix(Nq, kint,mxREAL);//costruisce l'output array
    idcdouble = mxGetPr(plhs[0]);//appicicaci il puntatore 
    
    
    GLTREE *Tree;//dichiaro il puntatore l'oggetto
    
    Tree=(GLTREE*)((long)(ptrtree[0]));//ritrasformo il puntatore passato
    
//     mexPrintf("puntatore= %4.4x\n",Tree);
    
   
    //x e y sono i vettori dei reference points passati
    //pk � un array [2x1] con x e y del query point
    //idc double � l'id del pi� vicino, sarebbe un integer ma per ridare il puntatore a double
    
    
    int* idc=new int[kint];
    double* distances=new double[kint];
    //Run all the queries
   
    //declaration
    //void GLTREE::SearchKClosest(Coord3D *p,Coord3D *pk,int* idc,double* mindist,int k)
    
     Coord3D* pstruct=new Coord3D[N]; 
       
      //copying the point array to GLTree data structure
      for (i=0;i<N;i++)
      {
          
       pstruct[i].x=p[i];
        pstruct[i].y=p[i+N];
         pstruct[i].z=p[i+2*N];
       
      }
    
 
    if (nlhs==1)//ricerca solo id punti
    {
        for (i=0;i<Nq;i++)
        {
//               mexPrintf("Prima della ricerca");
            pk.x=qp[i];pk.y=qp[i+Nq];pk.z=qp[i+Nq+Nq];
            Tree->SearchKClosest(&pstruct[0],&pk,idc,distances,kint);//lancio la routine per la ricerca del pi� vicino
//            mexPrintf("Dopo la ricerca");
            for (j=0;j<kint;j++)
            {
                idcdouble[Nq*j+i]=idc[j]+1;//convert to matlab notation
            }
        }
    }
    else//Ricerca con distanze
    {
        plhs[1] = mxCreateDoubleMatrix(Nq, kint,mxREAL);//costruisce l'output array
        outdistances = mxGetPr(plhs[1]);//appicicaci il puntatore
        for (i=0;i<Nq;i++)
        {
                       pk.x=qp[i];pk.y=qp[i+N];pk.z=qp[i+N+N];
            Tree->SearchKClosest(pstruct,&pk,idc,distances,kint);//lancio la routine per la ricerca del pi� vicino
            for (j=0;j<kint;j++)
            {
                idcdouble[Nq*(j)+i]=idc[j]+1;//convert to matlab notation
                outdistances[Nq*(j)+i]=distances[j];
            }
        }
    }
    //Free aloocated memory
    delete [] idc;
    delete [] distances;
    delete [] pstruct;
}





