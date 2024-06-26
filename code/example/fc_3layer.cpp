#include "inc/common.h"
#include "inc/core.h"
#include "inc/dataloader.h"
#include "inc/help.h"

#include <chrono>

/**
 * the mathamatical derivation is provided in the document:
 * doc/backpropagation.md
 */

#define BATCH_SIZE 256
#define INPUT_NODE 784
#define L1_NODE 128
#define L2_NODE 64
#define OUTPUT_NODE 10
float LEARNING_RATE = 0.01 / BATCH_SIZE;

using namespace Potato::Op;
using namespace Potato::Activ;

int main(int argc, char **argv)
{

    UNUSED(argc);
    UNUSED(argv);

    auto mnist = Potato::DataLoader::mnistDataLoader("data/train.txt");
    int ret = mnist.init();
    if (ret != 0)
    {
        std::cout << "Init test fail: should return 0, but " << ret << std::endl;
        return ret;
    }

    printf("learning rate is %f\n", LEARNING_RATE);

    std::vector<float> input_node, y_lable; // (BATCH_SIZE * INPUT_NODE); will be filled by mnist_get_random()

    std::vector<float> l1_node(INPUT_NODE * L1_NODE);
    Potato::helper::random_init(l1_node, INPUT_NODE * L1_NODE);
    // l1 bias
    std::vector<float> l1_bias(L1_NODE);
    Potato::helper::random_init(l1_bias, L1_NODE);

    std::vector<float> l2_node(L1_NODE * L2_NODE);
    Potato::helper::random_init(l2_node, L1_NODE * L2_NODE);
    // l2 bias
    std::vector<float> l2_bias(L2_NODE);
    Potato::helper::random_init(l2_bias, L2_NODE);

    std::vector<float> output_node(L2_NODE * OUTPUT_NODE);
    Potato::helper::random_init(output_node, L2_NODE * OUTPUT_NODE);
    // output bias
    std::vector<float> output_bias(OUTPUT_NODE);
    Potato::helper::random_init(output_bias, OUTPUT_NODE);

    // time measurement
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int echo = 0; echo < 10000; echo++)
    {
        mnist.random_get_trainning(input_node, y_lable, BATCH_SIZE);

        // normalize the input in case of overflow
        normalize<std::vector<float>, float>(
            input_node, input_node, BATCH_SIZE * INPUT_NODE);

        // forward propagation
        static std::vector<float> a1(BATCH_SIZE * L1_NODE);
        dot<std::vector<float>, float>(
            input_node, l1_node, a1, BATCH_SIZE, INPUT_NODE, L1_NODE);
        add_vec_to_batch_vec<std::vector<float>>(a1, l1_bias, a1, BATCH_SIZE, L1_NODE);
        relu<std::vector<float>>(a1, a1, BATCH_SIZE * L1_NODE);

        static std::vector<float> a2(BATCH_SIZE * L2_NODE);
        dot<std::vector<float>, float>(
            a1, l2_node, a2, BATCH_SIZE, L1_NODE, L2_NODE);
        add_vec_to_batch_vec<std::vector<float>>(a2, l2_bias, a2, BATCH_SIZE, L2_NODE);
        relu<std::vector<float>>(a2, a2, BATCH_SIZE * L2_NODE);

        static std::vector<float> yp(BATCH_SIZE * OUTPUT_NODE);
        dot<std::vector<float>, float>(
            a2, output_node, yp, BATCH_SIZE, L2_NODE, OUTPUT_NODE);
        add_vec_to_batch_vec<std::vector<float>>(yp, output_bias, yp, BATCH_SIZE, OUTPUT_NODE);
        softmax<std::vector<float>, float>(yp, yp, BATCH_SIZE, OUTPUT_NODE);

        // back propagation
        static std::vector<float> Loss_m(BATCH_SIZE * OUTPUT_NODE);
        diff<std::vector<float>>(
            yp, y_lable, Loss_m, BATCH_SIZE * OUTPUT_NODE);
        // dz3 =L,  dW3 = a2.T * Loss_m
        static std::vector<float> dW3(L2_NODE * OUTPUT_NODE);
        static std::vector<float> a2_T(L2_NODE * BATCH_SIZE);
        transpose<std::vector<float>, float>(a2, BATCH_SIZE, L2_NODE, a2_T);
        dot<std::vector<float>, float>(
            a2_T, Loss_m, dW3, L2_NODE, BATCH_SIZE, OUTPUT_NODE);

        // dz2 = dz3 * W3.T x Relu'(a2)
        static std::vector<float> dz2(BATCH_SIZE * L2_NODE);
        static std::vector<float> output_node_T(OUTPUT_NODE * L2_NODE);
        transpose<std::vector<float>, float>(output_node, L2_NODE, OUTPUT_NODE, output_node_T);
        dot<std::vector<float>, float>(
            Loss_m, output_node_T, dz2, BATCH_SIZE, OUTPUT_NODE, L2_NODE);
        reluPrime<std::vector<float>>(a2, a2, BATCH_SIZE * L2_NODE);
        times<std::vector<float>>(dz2, a2, dz2, BATCH_SIZE * L2_NODE);

        // dW2 = a1.T * dz2
        static std::vector<float> a1_T(L1_NODE * BATCH_SIZE);
        transpose<std::vector<float>, float>(a1, BATCH_SIZE, L1_NODE, a1_T);
        static std::vector<float> dW2(L1_NODE * L2_NODE);
        dot<std::vector<float>, float>(
            a1_T, dz2, dW2, L1_NODE, BATCH_SIZE, L2_NODE);

        // dz1 = dz2 * W2.T x Relu'(a1)
        static std::vector<float> dz1(BATCH_SIZE * L1_NODE);
        static std::vector<float> l2_node_T(L2_NODE * L1_NODE);
        transpose<std::vector<float>, float>(l2_node, L1_NODE, L2_NODE, l2_node_T);
        dot<std::vector<float>, float>(
            dz2, l2_node_T, dz1, BATCH_SIZE, L2_NODE, L1_NODE);
        reluPrime<std::vector<float>>(a1, a1, BATCH_SIZE * L1_NODE);
        times<std::vector<float>>(dz1, a1, dz1, BATCH_SIZE * L1_NODE);

        // dW1 = input.T * dz1
        static std::vector<float> input_node_T(INPUT_NODE * BATCH_SIZE);
        transpose<std::vector<float>, float>(input_node, BATCH_SIZE, INPUT_NODE, input_node_T);
        static std::vector<float> dW1(INPUT_NODE * L1_NODE);
        dot<std::vector<float>, float>(
            input_node_T, dz1, dW1, INPUT_NODE, BATCH_SIZE, L1_NODE);

        // update W1 W2 W3
        factor<std::vector<float>, float>(dW3, LEARNING_RATE, dW3, L2_NODE * OUTPUT_NODE);
        diff<std::vector<float>>(output_node, dW3, output_node, L2_NODE * OUTPUT_NODE);

        factor<std::vector<float>, float>(dW2, LEARNING_RATE, dW2, L1_NODE * L2_NODE);
        diff<std::vector<float>>(l2_node, dW2, l2_node, L1_NODE * L2_NODE);

        factor<std::vector<float>, float>(dW1, LEARNING_RATE, dW1, INPUT_NODE * L1_NODE);
        diff<std::vector<float>>(l1_node, dW1, l1_node, INPUT_NODE * L1_NODE);

        // update bias
        factor<std::vector<float>, float>(Loss_m, -LEARNING_RATE, Loss_m, BATCH_SIZE * OUTPUT_NODE);
        add_batch_vec_to_vec<std::vector<float>>(Loss_m, output_bias, output_bias, BATCH_SIZE, OUTPUT_NODE);

        factor<std::vector<float>, float>(dz2, -LEARNING_RATE, dz2, BATCH_SIZE * L2_NODE);
        add_batch_vec_to_vec<std::vector<float>>(dz2, l2_bias, l2_bias, BATCH_SIZE, L2_NODE);

        factor<std::vector<float>, float>(dz1, -LEARNING_RATE, dz1, BATCH_SIZE * L1_NODE);
        add_batch_vec_to_vec<std::vector<float>>(dz1, l1_bias, l1_bias, BATCH_SIZE, L1_NODE);

        if (echo % 100 == 0)
        {
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end_time - start_time;
            std::cout << "Each echo takes:"
                      << diff.count() / 100.0 * 1000 << " ms" << std::endl;
            start_time = std::chrono::high_resolution_clock::now();

            float loss =
                Potato::Loss::MSE<std::vector<float>, float>(yp, y_lable, BATCH_SIZE * OUTPUT_NODE);
            std::cout << "Loss is:" << loss * OUTPUT_NODE << std::endl;

            // test accuracy
            int correct = 0;
            for (int i = 0; i < BATCH_SIZE; i++)
            {
                int max_idx = 0;
                float max_val = yp[i * OUTPUT_NODE];
                for (int j = 1; j < OUTPUT_NODE; j++)
                {
                    if (yp[i * OUTPUT_NODE + j] > max_val)
                    {
                        max_val = yp[i * OUTPUT_NODE + j];
                        max_idx = j;
                    }
                }
                if (y_lable[i * OUTPUT_NODE + max_idx] == 1)
                {
                    correct++;
                }
            }
            std::cout << "Accuracy is:" << correct * 1.0 / BATCH_SIZE << std::endl;
        }
    }
}