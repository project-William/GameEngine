#include "Shader.h"
#include <fstream>
#include "Tools/Logger.h"

Shader::Shader(vk::Device device, std::string fileName, EShLanguage stage, file_tag) {
    ShaderCompiler compiler;

    log("Try to Compile shader : " + fileName);

    try {
        auto code = compiler.compileFromFile(fileName, stage, false, false);

        vk::ShaderModuleCreateInfo info;
        info.codeSize = code.size() * sizeof(decltype(code)::value_type);
        info.pCode = reinterpret_cast<const uint32_t*>(code.data());
        static_cast<vk::UniqueShaderModule&>(*this) = device.createShaderModuleUnique(info);
    }

    catch(std::runtime_error &error) {
        log(error);
        throw;
    }

    log("Success");
}

Shader::Shader(vk::Device device, std::string source, EShLanguage stage, source_tag) {
    ShaderCompiler compiler;

    log("Try to Compile shader from source : ");

    try {
        auto code = compiler.compileFromSource(source, stage, false, false);

        vk::ShaderModuleCreateInfo info;
        info.codeSize = code.size() * sizeof(decltype(code)::value_type);
        info.pCode = reinterpret_cast<const uint32_t*>(code.data());
        static_cast<vk::UniqueShaderModule&>(*this) = device.createShaderModuleUnique(info);
    }

    catch(std::runtime_error &error) {
        log(error);
        throw;
    }

    log("Success");
}
