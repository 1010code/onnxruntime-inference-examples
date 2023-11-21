#include <onnxruntime_cxx_api.h>

#include <array>
#include <iostream>

using namespace std;

int main()
{
    Ort::Env env;
    Ort::Session session{env, "./data/tf_model.onnx", Ort::SessionOptions{}};

    Ort::AllocatorWithDefaultOptions allocator;
    // 取得 input 和 output 名稱
    auto temp_input_name = session.GetInputNameAllocated(0, allocator);
    auto *input_name = temp_input_name.get();
    auto temp_output_name = session.GetOutputNameAllocated(0, allocator);
    auto *output_name = temp_output_name.get();
    // 配置輸入/出節點名稱
    std::array input_names = {input_name};
    std::array output_names = {output_name};
    std::cout << "inputNames: " << input_names[0] << std::endl;
    std::cout << "outputNames: " << output_names[0] << std::endl;
    //     std::cout << "out siz: " << session.GetOutputTypeInfo(1).GetONNXType() << std::endl; // 直接從ONNX解析輸出格式
    // 取得 input shape
    auto input_shape = session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
    // 允許只有一筆資料
    input_shape[0] = 1;

    // 設定 input data
    std::vector<float> input_values = {6.7, 3.1, 4.4, 1.4};
    // 配置 tensors 空間
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    // 建立 input tensor
    auto input_onnx_tensor = Ort::Value::CreateTensor<float>(memory_info, input_values.data(), input_values.size(), input_shape.data(), input_shape.size());
    // ONNXRuntime 推論
    auto output_values = session.Run(Ort::RunOptions{nullptr},
                                     input_names.data(), &input_onnx_tensor, 1,
                                     output_names.data(), 1);

    auto &output = output_values[0];                       // 取得推論結果
    auto output_type = output.GetTypeInfo().GetONNXType(); // 取得輸出格式分配解析器
                                                           /**
                                                            *   處理 output 為 tensor type
                                                            *  type: float32, int64 tensor
                                                            */
    if (output_type == ONNX_TYPE_TENSOR)
    {
        auto tensor_type = output.GetTensorTypeAndShapeInfo().GetElementType();
        if (tensor_type == ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64)
        {
            // 會跑到這邊的有 sklearn 分類模型 Sklearn output_label int64[?]
            auto *ints = output.GetTensorMutableData<int>(); // Get pointer to output tensor int values
            const auto ints_count = output.GetTensorTypeAndShapeInfo().GetElementCount();
            // pointer array to vector
            std::vector<int> values(ints, ints + ints_count);
            std::cout << "Sklearn out: " << values[0] << std::endl;
        }
        else
        {
            // 會跑到這的有 TF 和 sklearn 迴歸模型
            auto *floats = output.GetTensorMutableData<float>(); // Get pointer to output tensor float values
            const auto floats_count = output.GetTensorTypeAndShapeInfo().GetElementCount();
            // pointer array to vector
            std::vector<double> values(floats, floats + floats_count);
            std::cout << "TF out: " << values[0] << " " << values[1] << " " << values[2] << std::endl;
        }
    }
    /**
     *  處理 sklearn 分類器 output_probability
     *  type: sequence<map<int64,float32>>
     */
    else if (output_type == ONNX_TYPE_SEQUENCE)
    {
        std::cout << "sequence_type: " << output.GetTypeInfo().GetSequenceTypeInfo().GetSequenceElementType() << std::endl;
        // 解析輸出 sequence map
        size_t num_values = output.GetCount(); // 預設只有一筆推論，因此回傳1
        std::cout << "num_values: " << num_values << std::endl;
        Ort::Value map_out = output.GetValue(static_cast<int>(0), allocator); // 解析第一組 map
        // 取得 keys => one-hot label
        Ort::Value keys_ort = map_out.GetValue(0, allocator);
        int *keys_ret = keys_ort.GetTensorMutableData<int>();
        std::cout << "out: " << keys_ret[0] << " " << keys_ret[1] << " " << keys_ret[2] << std::endl;
        // 取得 values => label probability
        Ort::Value values_ort = map_out.GetValue(1, allocator);
        float *values_ret = values_ort.GetTensorMutableData<float>();
        std::cout << "out: " << values_ret[0] << " " << values_ret[1] << " " << values_ret[2] << std::endl;
    }
}