
#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#include <string.h>
#include <jni.h>

#include "benchmarks.h"

FILE * perfLog;

extern "C" {

    JNIEXPORT jstring JNICALL
         Java_com_example_droidinia_MainActivity_BenchmarksFromJNI( JNIEnv* env,
                                                                   jobject thiz,
																   jint choice[]) {
         #if defined(__arm__)
             #if defined(__ARM_ARCH_7A__)
               #if defined(__ARM_NEON__)
                 #if defined(__ARM_PCS_VFP)
                   #define ABI "armeabi-v7a/NEON (hard-float)"
                 #else
                   #define ABI "armeabi-v7a/NEON"
                 #endif
               #else
                 #if defined(__ARM_PCS_VFP)
                   #define ABI "armeabi-v7a (hard-float)"
                 #else
                   #define ABI "armeabi-v7a"
                 #endif
               #endif
             #else
              #define ABI "armeabi"
             #endif
         #elif defined(__i386__)
             #define ABI "x86"
         #elif defined(__x86_64__)
             #define ABI "x86_64"
         #elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
             #define ABI "mips64"
         #elif defined(__mips__)
             #define ABI "mips"
         #elif defined(__aarch64__)
         #define ABI "arm64-v8a"
         #else
             #define ABI "unknown"
         #endif

        perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "w");
 	    if (!perfLog) {
 	        printf("\nCannot open /sdcard/Droidinia-Output/logfile.txt for writing.\n");
 	        return env->NewStringUTF("Everything failed.");  // bail out if we can't log
 	    }
 	    fprintf(perfLog, "Starting benchmarks!");
 	    fclose(perfLog);
    	helper(choice);

         return env->NewStringUTF("Yo bruh, compiled with " ABI ".");

    }
}






//Forward declaration of mainRunBFS function
int mainRunBFS(char * argv[]);


char *file_contents(const char *filename, int *length)
{
    FILE *f = fopen(filename, "r");
    void *buffer;

    if (!f) {
        LOGE("Unable to open %s for reading\n", filename);
        return (NULL);
    }

    fseek(f, 0, SEEK_END);
    *length = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = malloc(*length+1);
    *length = fread(buffer, 1, *length, f);
    fclose(f);
    ((char*)buffer)[*length] = '\0';

    return ((char*)buffer);
}

bool throwJavaException(JNIEnv *env,std::string method_name,std::string exception_msg, int errorCode=0)
{
    char buf[8];
    sprintf(buf,"%d",errorCode);
    std::string code(buf);

    std::string msg = "@" + method_name + ": " + exception_msg + " ";
    if(errorCode!=0) msg += code;

    jclass generalExp = env->FindClass("java/lang/Exception");
    if (generalExp != 0) {
        env->ThrowNew(generalExp, msg.c_str());
        return (true);
    }
    return (false);
}

void cb(cl_program p,void* data)
{
    clRetainProgram(p);
    cl_device_id devid[1];
    clGetProgramInfo(p,CL_PROGRAM_DEVICES,sizeof(cl_device_id),(void*)devid,NULL);
    char bug[65536];
    clGetProgramBuildInfo(p,devid[0],CL_PROGRAM_BUILD_LOG,65536*sizeof(char),bug,NULL);
    clReleaseProgram(p);
    LOGE("Build log \n %s\n",bug);
}


void helper(int choice[])
{
	int set_NDRange_size=16;
	char* filePathptr;
	int result = 0;

	//opening file and closing. Appended to in later locations
	 perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
	    if (!perfLog) {
	        printf("\nCannot open /sdcard/Droidinia-Output/logfile.txt for writing.\n");
	        return;   // bail out if we can't log
	    }

 	    fprintf(perfLog, "\nGoing through massive benchmark list");


    try {
        if (choice[0]==1) { //leukocyte


        }
        if (choice[1]==1){ //heartwall

        }

        if (choice[2]==1){ //CFD

        }

        if (choice[3]==1){ //LUdecomp

        }

        if (choice[4]==1){ //hotspot

        }

        if (choice[5]==1){ //backprop

        }

        if (choice[6]==1){ //needleman

        }

        if (choice[7]==1){ //kmeans

        }

       // if (choice[8]==1){ //BFS
        	fprintf(perfLog, "\nEntered BFS location\n");
        	fclose(perfLog);
        	//char filePath[] = "/sdcard/Droidinia-Output/graph4096.txt";
        	char filePath[] = "/sdcard/Droidinia-Output/graph65536.txt";
        	filePathptr = &filePath[0];
        	result = mainRunBFS(&filePathptr);
        	perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
        	fprintf(perfLog, "\nTHE VALUE FOR mainRunBFS: %d", result);
        	fclose(perfLog);
        	if (result < 0) {
        		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
        		fprintf(perfLog, "\n\n----------\nError in running mainRunBFS\n----------\n\n");
        		fclose(perfLog);
        	}
        //}

        if (choice[9]==1){ //srad

        }

        if (choice[10]==1){ //streamcluster

        }

        if (choice[11]==1){ //particle filter

        }

        if (choice[12]==1){ //pathfinder

        }

        if (choice[13]==1){ //gaussian

        }

        if (choice[14]==1){ //k nearest

        }

        if (choice[15]==1){ //lava

        }

        if (choice[16]==1){ //myocyte

        }

        if (choice[17]==1){ //btree

        }

        if (choice[18]==1){ //gpudwt

        }

        if (choice[19]==1){ //hybrid sort

        }

        //last arg in this should be out???
        //gQueue.enqueueReadBuffer(bufferOut, CL_TRUE, 0, isize*sizeof(cl_uchar4), NULL);

    }
    catch (cl::Error e) {
        LOGI("@oclDecoder: %s %d \n",e.what(),e.err());
    }
    if(perfLog) {
    	fclose(perfLog);
    }
}

//public double CPUSPEED;
/* ------------------------------------------------------
 * FROM timer.cc
 ------------------------------------------------------*/

double getCPUSpeedinHz() {
	double cSpeed = 0.0;
	FILE* cpufile = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
	fscanf (cpufile, "%lf", &cSpeed);
	fclose(cpufile);
	return cSpeed;
}


double timer::CPU_speed_in_MHz = timer::get_CPU_speed_in_MHz();

double timer::get_CPU_speed_in_MHz() {
    double cpuSpeed = 0.0;
#if defined ABI
	FILE* cpufile = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
	fscanf (cpufile, "%lf", &cpuSpeed);
	fclose(cpufile);
	perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
	fprintf(perfLog, "\nTHE VALUE FOR cpuSpeed %f", cpuSpeed);
	fclose(perfLog);
#endif
	//CPUSPEED = (double)cpuSpeed;
	return (cpuSpeed/1000);
}

//   /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq
/*
#if defined __linux__
    ifstream infile("/proc/cpuinfo");
    char     buffer[256], *colon;

    while (infile.good()) {
	infile.getline(buffer, 256);

	if (strncmp("cpu MHz", buffer, 7) == 0 && (colon = strchr(buffer, ':')) != 0)
	    return atof(colon + 2);
    }
#endif

    return (0.0);
}*/

void timer::print_time(ostream &str, const char *which, double time) const
{
    static const char *units[] = { " ns", " us", " ms", "  s", " ks", 0 };
    const char	      **unit   = units;

    time = 1000.0 * time / CPU_speed_in_MHz;

    while (time >= 999.5 && unit[1] != 0) {
	time /= 1000.0;
	++ unit;
    }

    str << which << " = " << setprecision(3) << setw(4) << time << *unit;
}

ostream &timer::print(ostream &str)
{
    str << left << setw(25) << (name != 0 ? name : "timer") << ": " << right;

    if (CPU_speed_in_MHz == 0)
	str << "could not determine CPU speed\n";
    else if (count > 0) {
	double total = static_cast<double>(total_time);

	print_time(str, "avg", total / static_cast<double>(count));
	print_time(str, ", total", total);
	str << ", count = " << setw(9) << count << '\n';
    }
    else
	str << "not used\n";

    return (str);
}

ostream &operator << (ostream &str, class timer &timer)
{
    return (timer.print(str));
}

double timer::getTimeInSeconds()
{
    double total = static_cast<double>(total_time);
    double res = (total / 1000000.0) / CPU_speed_in_MHz;

    perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
    fprintf(perfLog, "\nThe total time taken, in some unit: %f", total);
    fprintf(perfLog, "\nThe CPU Speed: %d", (int) CPU_speed_in_MHz);
    fclose(perfLog);

    return (res);
}



/*--------------------------------------
 * FROM bfs.cpp:
 */
//Structure to hold a node information, also found in kernels.cl
struct Node
{
	int starting;
	int no_of_edges;
};

//----------------------------------------------------------
//--breadth first search on GPUs
//----------------------------------------------------------
void run_bfs_gpu(int no_of_nodes, Node *h_graph_nodes, int edge_list_size, \
		int *h_graph_edges, char *h_graph_mask, char *h_updating_graph_mask, \
		char *h_graph_visited, int *h_cost)
					throw(std::string){

	//int number_elements = height*width;
	char h_over;
	cl_mem d_graph_nodes, d_graph_edges, d_graph_mask, d_updating_graph_mask, \
			d_graph_visited, d_cost, d_over;
	try{
		//--1 transfer data from host to device
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		fprintf(perfLog, "\nAbou to run _clInit().");
		fclose(perfLog);
		_clInit();
		d_graph_nodes = _clMalloc(no_of_nodes*sizeof(Node), h_graph_nodes);
		d_graph_edges = _clMalloc(edge_list_size*sizeof(int), h_graph_edges);
		d_graph_mask = _clMallocRW(no_of_nodes*sizeof(char), h_graph_mask);
		d_updating_graph_mask = _clMallocRW(no_of_nodes*sizeof(char), h_updating_graph_mask);
		d_graph_visited = _clMallocRW(no_of_nodes*sizeof(char), h_graph_visited);


		d_cost = _clMallocRW(no_of_nodes*sizeof(int), h_cost);
		d_over = _clMallocRW(sizeof(char), &h_over);

		_clMemcpyH2D(d_graph_nodes, no_of_nodes*sizeof(Node), h_graph_nodes);
		_clMemcpyH2D(d_graph_edges, edge_list_size*sizeof(int), h_graph_edges);
		_clMemcpyH2D(d_graph_mask, no_of_nodes*sizeof(char), h_graph_mask);
		_clMemcpyH2D(d_updating_graph_mask, no_of_nodes*sizeof(char), h_updating_graph_mask);
		_clMemcpyH2D(d_graph_visited, no_of_nodes*sizeof(char), h_graph_visited);
		_clMemcpyH2D(d_cost, no_of_nodes*sizeof(int), h_cost);

		//--2 invoke kernel
		timer kernel_timer;
		double kernel_time = 0.0;
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		fprintf(perfLog, "\nAbout to reset kernel_timer.");
		fclose(perfLog);
		kernel_timer.reset();
		kernel_timer.start();
		clock_t startingPoint, endingPoint;
		startingPoint = clock();
		do{
			h_over = false;
			_clMemcpyH2D(d_over, sizeof(char), &h_over);
			//--kernel 0
			int kernel_id = 0;
			int kernel_idx = 0;
			_clSetArgs(kernel_id, kernel_idx++, d_graph_nodes);
			_clSetArgs(kernel_id, kernel_idx++, d_graph_edges);
			_clSetArgs(kernel_id, kernel_idx++, d_graph_mask);
			_clSetArgs(kernel_id, kernel_idx++, d_updating_graph_mask);
			_clSetArgs(kernel_id, kernel_idx++, d_graph_visited);
			_clSetArgs(kernel_id, kernel_idx++, d_cost);
			_clSetArgs(kernel_id, kernel_idx++, &no_of_nodes, sizeof(int));

			//int work_items = no_of_nodes;
			_clInvokeKernel(kernel_id, no_of_nodes, work_group_size);

			//--kernel 1
			kernel_id = 1;
			kernel_idx = 0;
			_clSetArgs(kernel_id, kernel_idx++, d_graph_mask);
			_clSetArgs(kernel_id, kernel_idx++, d_updating_graph_mask);
			_clSetArgs(kernel_id, kernel_idx++, d_graph_visited);
			_clSetArgs(kernel_id, kernel_idx++, d_over);
			_clSetArgs(kernel_id, kernel_idx++, &no_of_nodes, sizeof(int));

			//work_items = no_of_nodes;
			_clInvokeKernel(kernel_id, no_of_nodes, work_group_size);

			_clMemcpyD2H(d_over,sizeof(char), &h_over);
			}while(h_over);

		_clFinish();
		kernel_timer.stop();
		endingPoint = clock();
		kernel_time = (int)(kernel_timer.getTimeInSeconds());
		//--3 transfer data from device to host
		_clMemcpyD2H(d_cost,no_of_nodes*sizeof(int), h_cost);
		//--statistics
		//FILE *bfsLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");

        fprintf(perfLog, "\nKernel Time(s): %f\n", kernel_time);
		//std::cout<<"kernel time(s):"<<kernel_time<<std::endl;
		fprintf(perfLog, "\nUsing clock, %f", (double)(endingPoint - startingPoint) / getCPUSpeedinHz());
		fclose(perfLog);

		//--4 release cl resources.
		_clFree(d_graph_nodes);
		_clFree(d_graph_edges);
		_clFree(d_graph_mask);
		_clFree(d_updating_graph_mask);
		_clFree(d_graph_visited);
		_clFree(d_cost);
		_clFree(d_over);
		_clRelease();
	}
	catch(std::string msg){
		_clFree(d_graph_nodes);
		_clFree(d_graph_edges);
		_clFree(d_graph_mask);
		_clFree(d_updating_graph_mask);
		_clFree(d_graph_visited);
		_clFree(d_cost);
		_clFree(d_over);
		_clRelease();
		std::string e_str = "in run_transpose_gpu -> ";
		e_str += msg;
		throw(e_str);
	}
	return ;
}
void Usage(int argc, char**argv){
	FILE *log = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
	fprintf(log, "Usage: %s <input file>\n", argv[0]);
	//fprintf(stderr,"Usage: %s <input_file>\n", argv[0]);
	fclose(log);
}
//----------------------------------------------------------
//--cambine:	main function
//--author:		created by Jianbin Fang
//--date:		25/01/2011
//----------------------------------------------------------
int mainRunBFS(char * argv[])
{
	//opening file in some location to log results, etc.
	 perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
	    if (!perfLog) {
	        printf("\nCannot open /sdcard/Droidinia-Output/logfile.txt for appending.\n");
	        return (-1);   // bail out if we can't log
	    }


	int no_of_nodes;
	int edge_list_size;
	FILE *fp;
	int argc = 4; //was originally a main argument of function
	Node* h_graph_nodes;
	char *h_graph_mask, *h_updating_graph_mask, *h_graph_visited;
	try{
		char *input_f;
		/*
		if(argc!=2){
		  fclose(log);
		  Usage(argc, argv);
		  exit(0);
		}*/

		input_f = argv[0]; //changed to 0 because of how c string is handled in helper?
		fprintf(perfLog, "Reading File\n");
		//printf("Reading File\n");
		//Read in Graph from a file
		fp = fopen(input_f,"r");
		if(!fp){
		  fprintf(perfLog, "Error Reading Graph file\n");
		  //printf("Error Reading graph file\n");
		  fclose(perfLog);
		  return (-1);
		}
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		fprintf(perfLog, "\nSuccessfully Read Graph File.");
		fclose(perfLog);

		int source = 0;

		fscanf(fp,"%d",&no_of_nodes);

		int num_of_blocks = 1;
		int num_of_threads_per_block = no_of_nodes;

		//Make execution Parameters according to the number of nodes
		//Distribute threads across multiple Blocks if necessary
		if(no_of_nodes>MAX_THREADS_PER_BLOCK){
			num_of_blocks = (int)ceil(no_of_nodes/(double)MAX_THREADS_PER_BLOCK);
			num_of_threads_per_block = MAX_THREADS_PER_BLOCK;
		}
		work_group_size = num_of_threads_per_block;
		// allocate host memory
		h_graph_nodes = (Node*) malloc(sizeof(Node)*no_of_nodes);
		h_graph_mask = (char*) malloc(sizeof(char)*no_of_nodes);
		h_updating_graph_mask = (char*) malloc(sizeof(char)*no_of_nodes);
		h_graph_visited = (char*) malloc(sizeof(char)*no_of_nodes);

		int start, edgeno;
		// initalize the memory
		for(int i = 0; i < no_of_nodes; i++){
			fscanf(fp,"%d %d",&start,&edgeno);
			h_graph_nodes[i].starting = start;
			h_graph_nodes[i].no_of_edges = edgeno;
			h_graph_mask[i]=false;
			h_updating_graph_mask[i]=false;
			h_graph_visited[i]=false;
		}
		//read the source node from the file
		fscanf(fp,"%d",&source);
		source=0;
		//set the source node as true in the mask
		h_graph_mask[source]=true;
		h_graph_visited[source]=true;
    	fscanf(fp,"%d",&edge_list_size);
   		int id,cost;
		int* h_graph_edges = (int*) malloc(sizeof(int)*edge_list_size);
		for(int i=0; i < edge_list_size ; i++){
			fscanf(fp,"%d",&id);
			fscanf(fp,"%d",&cost);
			h_graph_edges[i] = id;
		}

		if(fp)
			fclose(fp);
		// allocate mem for the result on host side
		int	*h_cost = (int*) malloc(sizeof(int)*no_of_nodes);
		int *h_cost_ref = (int*)malloc(sizeof(int)*no_of_nodes);
		for(int i=0;i<no_of_nodes;i++){
			h_cost[i]=-1;
			h_cost_ref[i] = -1;
		}
		h_cost[source]=0;
		h_cost_ref[source]=0;
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		fprintf(perfLog, "\nAbout to run_bfs_gpu.");
		fclose(perfLog);
		//---------------------------------------------------------
		//--gpu entry
		run_bfs_gpu(no_of_nodes,h_graph_nodes,edge_list_size,h_graph_edges,
				h_graph_mask, h_updating_graph_mask, h_graph_visited, h_cost);
		//---------------------------------------------------------

		//release host memory
		free(h_graph_nodes);
		free(h_graph_mask);
		free(h_updating_graph_mask);
		free(h_graph_visited);

	}
	catch(std::string msg){
		perfLog = fopen("/sdcard/Droidinia-Output/logfile.txt", "a");
		fprintf(perfLog, "--combine: exception in main -> %s\n", msg.c_str());
		//std::cout<<"--combine: exception in main ->"<<msg<<std::endl;
		//release host memory
		free(h_graph_nodes);
		free(h_graph_mask);
		free(h_updating_graph_mask);
		free(h_graph_visited);
	}
	fprintf(perfLog, "I suppose it worked?");
	fclose(perfLog);

    return (0);
}













































































