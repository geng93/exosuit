/**************************************************
 * Written by jiekai for use in exosuit compliancy testing
 * Usage: pass in body parameters, exosuit tightness and lean angle to obtain force exerted on exosuit by a fixed length wire rope
 * 
 * Body parameters
 * ---------------------------------------------------------------------------
 * Age
 * Height (cm)
 * Weight (kg)
 * Total fat (100%)
 * Visceral fat (100%)
 * BMI (kg/cm/cm)
 * Subcutaneous Fat Body (100%)
 * Subcutaneous Fat Trunk (100%)
 * Subcutaneous Fat Arms (100%)
 * Subcutaneous Fat Legs (100%)
 * Skeletal Muscle Body (100%)
 * Skeletal Muscle Trunk (100%)
 * Skeletal Muscle Arms (100%)
 * Skeletal Muscle Legs (100%)
 * 
 * Exosuit Pressure (measured using a sphygmomanometer (blood pressure sensor) )
 * ------------------------------------------------------------------------------
 * Shoulder Right
 * Shoulder Left
 * Rib
 * Waist
 * Thigh Right
 * Thigh Left
 * 
 * Flexion Angle (deg)
 * Extension (cm)
 * Force due to extension (N)
 * 
 * Force due to extension is our label
 * 
 * To run training, set the "Train" precompiler variable to true
 * - The training snapshots will be saved in ./snapshots/exosuit_iter_[number].caffemodel
 * - the current learning rate, momentum etc of the solver is saved in ./snapshots/exosuit_iter_[number].solverstate
 * 
 * FILES
 * --------------------------------------------------------------------------
 * model.prototxt - used to state the network architecture, inputs, outputs and cost(loss) function
 * solver.prototxt - used to state the solver's learning rate, decay rate, momentum, max iterations, saved iterations etc
 * Experiment_raw_data.txt - the experiment raw data. Samples are saved in rows
 * matrix_io.cpp, matrix_io.hpp - 
 * 
 * Read the README file in Installation_Instructions for installation procedures
 * ***********************************************/

#include <caffe/caffe.hpp>
#include <memory>
#include "caffe/layers/memory_data_layer.hpp"
#include "matrix_io.h"
#include <iostream>

#define Train true
#define datasize 780

#define agescale 100
#define heightscale 200
#define weightscale 100
#define totalfatscale 100
#define visceralfatscale 100
#define bmiscale 100
#define subqbodyscale 100
#define subqtrunkscale 100
#define subqarmsscale 100
#define subqlegsscale 100
#define skebodyscale 100
#define sketrunkscale 100
#define skearmsscale 100
#define skelegsscale 100
#define rshoulderscale 100
#define lshoulderscale 100
#define ribscale 50
#define waistscale 100
#define rthighscale 50
#define lthighscale 50
#define anglescale 60
#define forcescale 200
#define extscale 20

int main()
{
  caffe::Caffe::set_mode(caffe::Caffe::CPU); //Caffe is a subset of caffe (note the capital and small letter C)

  // load data in from text file
  Eigen::MatrixXd dataset;
  MatrixIO mio;
  int cols = mio.readFromFile("Experiment_raw_data2.txt", dataset); 

  int batchsize = 10; //data are passed into the network in batches
  int numdata = dataset.rows();
  int epoch = 70 ; // each epoch will sum the error of the whole batch together
  int numaxis = 21; // remove the extension and force axis. the rest are input data
  int arraysize = batchsize*epoch*numaxis;

  float *input = new float[arraysize]; //dynamically assigned arrays allow bypassing of static assigned array limits
  float *label = new float[batchsize*epoch];

  for(int i=0; i<batchsize*epoch; i++)
  {
      input[0 + i*numaxis] = dataset(i,0)/agescale;
      input[1 + i*numaxis] = dataset(i,1)/heightscale;
      input[2 + i*numaxis] = dataset(i,2)/weightscale;
      input[3 + i*numaxis] = dataset(i,3)/totalfatscale;
      input[4 + i*numaxis] = dataset(i,4)/visceralfatscale;
      input[5 + i*numaxis] = dataset(i,5)/bmiscale;
      input[6 + i*numaxis] = dataset(i,6)/subqbodyscale;
      input[7 + i*numaxis] = dataset(i,7)/subqtrunkscale;
      input[8 + i*numaxis] = dataset(i,8)/subqarmsscale;
      input[9 + i*numaxis] = dataset(i,9)/subqlegsscale;
      input[10 + i*numaxis] = dataset(i,10)/skebodyscale;
      input[11 + i*numaxis] = dataset(i,11)/sketrunkscale;
      input[12 + i*numaxis] = dataset(i,12)/skearmsscale;
      input[13 + i*numaxis] = dataset(i,13)/skelegsscale;
      input[14 + i*numaxis] = dataset(i,14)/rshoulderscale;
      input[15 + i*numaxis] = dataset(i,15)/lshoulderscale;
      input[16 + i*numaxis] = dataset(i,16)/ribscale;
      input[17 + i*numaxis] = dataset(i,17)/waistscale;
      input[18 + i*numaxis] = dataset(i,18)/rthighscale;
      input[19 + i*numaxis] = dataset(i,19)/lthighscale;
      input[20 + i*numaxis] = dataset(i,20)/anglescale;

      label[i] = dataset(i,21)/extscale;
  }
  
  int t_batchsize = 10;
  int t_epoch = 16;
  //int skip = 4; //skip over a number of samples to obtain the test data
  float *t_input = new float[t_batchsize*t_epoch*numaxis]; //dynamically assigned arrays allow bypassing of static assigned array limits
  float *t_label = new float[t_batchsize*t_epoch];

  for(int i=0; i<t_batchsize*t_epoch; i++)
  {
      t_input[0 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),0)/agescale;
      t_input[1 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),1)/heightscale;
      t_input[2 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),2)/weightscale;
      t_input[3 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),3)/totalfatscale;
      t_input[4 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),4)/visceralfatscale;
      t_input[5 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),5)/bmiscale;
      t_input[6 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),6)/subqbodyscale;
      t_input[7 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),7)/subqtrunkscale;
      t_input[8 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),8)/subqarmsscale;
      t_input[9 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),9)/subqlegsscale;
      t_input[10 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),10)/skebodyscale;
      t_input[11 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),11)/sketrunkscale;
      t_input[12 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),12)/skearmsscale;
      t_input[13 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),13)/skelegsscale;
      t_input[14 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),14)/rshoulderscale;
      t_input[15 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),15)/lshoulderscale;
      t_input[16 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),16)/ribscale;
      t_input[17 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),17)/waistscale;
      t_input[18 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),18)/rthighscale;
      t_input[19 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),19)/lthighscale;
      t_input[20 + i*numaxis] = dataset((datasize-t_batchsize*t_epoch+i),20)/anglescale;

      t_label[i] = dataset((datasize-t_batchsize*t_epoch+i),21)/extscale;
    // printf("label[%d] = %f\n", i,t_input[12 + i*numaxis]);
  }
//   getchar();

#if Train
    // create a solver parameter object and load solver.prototxt into it
    caffe::SolverParameter solver_param;
    caffe::ReadSolverParamsFromTextFileOrDie("./solver.prototxt", &solver_param); //this will also load the model.prototxt as its name is recorded within solver.prototxt

    // Create solver out of the solver parameters
    boost::shared_ptr<caffe::Solver<float> > solver(caffe::SolverRegistry<float>::CreateSolver(solver_param));
    
    // obtain the input MemoryData layer from the solver’s neural network and feed in my training data
    caffe::MemoryDataLayer<float> *dataLayer_trainnet = (caffe::MemoryDataLayer<float> *) (solver->net()->layer_by_name("inputdata").get());
    caffe::MemoryDataLayer<float> *dataLayer_testnet_ = (caffe::MemoryDataLayer<float> *) (solver->test_nets()[0]->layer_by_name("test_inputdata").get());

    // Load the generated data into the net
    // The reset function of MemoryData allows you to provide pointers to the data
    dataLayer_trainnet->Reset(input, label, batchsize*epoch);
    dataLayer_testnet_->Reset(t_input, t_label, t_batchsize*t_epoch);

    // Copy trained layer from previous iteration
    // solver->net()->CopyTrainedLayersFrom("./snapshots/XOR_iter_5000000.caffemodel");

    // Call the solver to train the network
    solver->Solve();
#endif
    ///////////////////// NETWORK IS NOW TRAINED!! The rest is used to test the network ///////////////////////////

    // Create a network to just do forward propagation (NO NEED SOLVER)
    boost::shared_ptr<caffe::Net<float> > testnet;

    // Load the model.prototxt into the testnet
    testnet.reset(new caffe::Net<float>("./model.prototxt", caffe::TEST)); //Use the TEST phase to only load the test network. Train network will be auto loaded when we load the solver.prototxt as above
    
    // Copy the trained net parameters into the testnet. 
    // 1) either through a saved file from the solver or (2) copy directly from solver object since its a same project
    testnet->CopyTrainedLayersFrom("./snapshots/exosuit_iter_500000.caffemodel");
    // testnet->ShareTrainedLayersWith(solver->net().get());

    caffe::MemoryDataLayer<float> *dataLayer_testnet = (caffe::MemoryDataLayer<float> *) (testnet->layer_by_name("test_inputdata").get());

    //dataLayer_testnet->Reset(input, label, batchsize*epoch);
    dataLayer_testnet->Reset(t_input, t_label, t_batchsize*t_epoch);

    char filename[13];
    std::ofstream myfile;
	int n = sprintf(filename, "./results_ext.txt");
    myfile.open(filename, std::ios::out | std::ios::trunc);
	myfile.precision(18);
	myfile <<std::scientific;

    for (int i = 0; i < t_epoch; i++)
    {
        testnet->Forward();

        // access the output blob
        boost::shared_ptr<caffe::Blob<float> > output_blob = testnet->blob_by_name("output");
        //get the starting and ending position of the outputdata
        const float* begin = output_blob->cpu_data();
        const float* end = begin + t_batchsize;
        std::vector<float> result(begin, end); // create a vector that will store the output

        // access the label blob
        boost::shared_ptr<caffe::Blob<float> > label_blob = testnet->blob_by_name("label");
        //get the starting and ending position of the outputdata
        const float* tbegin = label_blob->cpu_data();
        const float* tend = tbegin + result.size();
        std::vector<float> mlabel(tbegin, tend); // create a vector that will store the result

        for(int i = 0; i< result.size(); ++i)
        {
            printf("NN output:%f, real output: %f\n", result[i], mlabel[i]);
        // printf("input: %d xor %d,  truth: %f result by nn: %f\n", (int)testab[i*2 + 0], (int)testab[i*2+1], testc[i], result[i]);
        }

        boost::shared_ptr<caffe::Blob<float>> loss_blob = testnet->blob_by_name("loss");
        const float *lbegin = loss_blob->cpu_data(); //must be cpu_data even though test is done on gpu
        const float *lend = lbegin + 1;           //total data size per batch
        std::vector<float> loss(lbegin, lend);
        printf("NN loss: %f\n", loss[0]);

        for (int k = 0; k < result.size(); k++)
        {
            myfile << result[k] << " " << mlabel[k]<< "\n";
        }

    }
    myfile.close();

	return 0;
}

