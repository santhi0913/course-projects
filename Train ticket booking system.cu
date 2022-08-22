#include<iostream>
#include<cuda.h>
#include <fstream>

using namespace std;


int **final;
class  Train
{
public:
    /* data */
    // int train_num;
    int num_class;
    int src;
    int dest;
    int *cls;

    void init_train(int num, int source, int destination){
        //  train_num = train;
         num_class = num;
         src = source;
         dest = destination;
         //cls = new int[num_class];
         cls = (int*)malloc(num_class*sizeof(int));
         
     }
   
};

class Request{
public:
    // int id;
    int train_num;
    int class_num;
    int source, desti, numSeats;
    void initialise( int tn , int cn, int src, int dest, int ns ){
        // id = id;
        train_num = tn;
        class_num = cn;
        source = src;
        desti = dest;
        numSeats = ns;
    }
};

// class Result
// {

// public:
//     int *occupied;
//     int *result;
//     void init_res(int num){

//     }
// };


__global__ void TrainTicket(int N, int R, Request *req,Train *train, int *result, int *occupied ){

    int tno = blockIdx.x*1000 + blockIdx.y;
    int cno = threadIdx.x;

    if(tno >= N) return;

    if(cno >= train[tno].num_class ) return;

    

    int start = train[tno].src;
    int base=(tno*25+cno)*51;
    

    for(int i=0; i<R; i++){
         
        if(req[i].train_num != tno || req[i].class_num != cno) continue;
        bool valid = true;

        for(int j= req[i].source- start ; j< req[i].desti-start; j++){
            if(occupied[base+j]+ req[i].numSeats > train[tno].cls[cno]){
                valid = false;
                result[i] =0;
                break;
            }
        }

        if(valid){
          for(int j= req[i].source- start ; j< req[i].desti-start; j++){
              occupied[base+j] += req[i].numSeats;
            }
            result[i] = 1;
        }

        
    }


}

// class Result{
//     public:
//     int *re;
//     int suc,fail;

//     void init_res(int n){
//         re = new int[n];
//     }
// };

void Major(int N){
    Train *train = new Train[N];
    Train *htrains = new Train[N];
    
    Train *d_train;
    int *d_occupied;    
    cudaMalloc(&d_occupied, N*25*51*sizeof(int));
    cudaMemset(d_occupied,0,N*25*51*sizeof(int)); 
    cudaMalloc(&d_train, N* sizeof(Train));
    
    
    for(int i=0; i<N; i++){
        int tid,ncls,sr,ds;
        cin >> tid >> ncls >> sr >> ds;
        if(sr>ds) swap(sr,ds);
        train[tid].init_train(ncls,sr,ds);
       
        for(int j=0; j<ncls; j++){
            int cid, mc;
            cin >> cid >> mc;
            train[tid].cls[cid] = mc;

        }
    }

    memcpy(htrains,train,N*sizeof(Train));
    for(int i=0;i<N;i++) {
        cudaMalloc(&htrains[i].cls ,train[i].num_class*sizeof(int));
        cudaMemcpy(htrains[i].cls,train[i].cls,train[i].num_class*sizeof(int),cudaMemcpyHostToDevice);
    }

    cudaMemcpy(d_train,htrains,N*sizeof(Train),cudaMemcpyHostToDevice);
    
    int* R;
    int B;
    Request **requuest;
    cin >> B;
    
    R = new int[B];
    requuest = new Request*[B];
    final = new int*[B];
    

    for(int i=0; i<B; i++){
        cin >> R[i];
        requuest[i] = new Request[R[i]];
        final[i] = new int[B];
        for(int j=0; j<R[i]; j++){
            int id,tn,cn,s,d,ns;
            cin >>id >>tn>>cn >> s >> d >> ns;
            if(s>d) swap(s,d);
            requuest[i][j].initialise(tn,cn,s,d,ns);
        }
    }

    

    for(int i=0; i<B; i++){
        Request* req = (Request*)malloc(R[i]*sizeof(Request));
        Request* d_req;
        cudaMalloc(&d_req ,R[i]*sizeof(Request));
        int *res = (int*)malloc(R[i]*sizeof(int));
        int *d_result;
        cudaMalloc(&d_result, R[i]*sizeof(int));
        cudaMemcpy(d_result, res, R[i]*sizeof(int), cudaMemcpyHostToDevice);

        for(int j=0; j<R[i];j++){
            req[j] = requuest[i][j];
        }

        cudaMemcpy(d_req,req,R[i]*sizeof(Request),cudaMemcpyHostToDevice);

        dim3 grid(ceil((double)N/(double)1000),1000,1);
        TrainTicket<<<grid,25>>>(N,R[i],d_req, d_train, d_result,d_occupied);
        cudaDeviceSynchronize();

        cudaMemcpy(res, d_result, R[i]*sizeof(int), cudaMemcpyDeviceToHost);
        
        //for(int j=0; j<R[i]; j++) final[i][j] = res[j];
        int nums=0, numf=0,sum=0;
        for(int j=0; j<R[i]; j++ ){
            // cout << res[j]<< " ";
            if(res[j] == 1) {
                cout << "success\n";
                nums++;
                sum += (req[j].numSeats )* (abs(req[j].source - req[j].desti));
            }
            else{
                cout << "failure\n";
                numf++;
            }
        }
        cout << nums << " " << numf << endl;
        
        cout << sum << endl;
        
    }
}
   


int main(){
    

    int N;
    cin >> N;
    Major(N);
    // for(int i=0; i<B; i++){
    //     int nums=0, numf=0,sum=0;
    //     for(int j=0; j<R[i]; j++ ){
    //         // cout << res[j]<< " ";
    //         if(final[i][j] == 1) {
    //             cout << "success\n";
    //             nums++;
    //             sum += (requuest[i][j].numSeats )* (abs(requuest[i][j].source - requuest[i][j].desti));
    //         }
    //         else{
    //             cout << "failure\n";
    //             numf++;
    //         }
    //     }
    //     cout << nums << " " << numf << endl;
        
    //     cout << sum << endl;
    // }
    
    return 0;
}
