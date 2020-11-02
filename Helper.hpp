//Thin collection of classes to assist in:
//	Checking validation layer support
//	Listing both instance extensions and device extensions
//	Finding both instance extensions and device extensions
//	Read from a file
//	Create a shader module 
namespace Helper
{
    //To use checkValidationlayerSupport, preferably use validationLayers
    const std::vector<const char*> validationLayers; 
    
    //Lists instance extensions
    void listIExtensions()
    {
        uint32_t iExtensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &iExtensionCount, nullptr);
        
        std::vector<VkExtensionProperties> iExtensions(iExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &iExtensionCount, iExtensions.data());

        std::cout << "Available instance extensions:\n";
        for (const auto& extension : iExtensions)
        {
            std::cout << "\t" << extension.extensionName << "\n";
        }
    }

    //Lists device extensions
    void listDExtensions(VkPhysicalDevice device)
    {
        uint32_t dExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &dExtensionCount, nullptr);
        std::vector<VkExtensionProperties> dExtensions(dExtensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &dExtensionCount, dExtensions.data());
        std::cout << "Available device extensions:\n";
        for (const auto& extension : dExtensions)
        {
            std::cout << "\t" << extension.extensionName << "\n";
        }
    }

    //Finds an instance extension
    bool findExtension(const char* extensionName)
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        //std::cout << "Available extensions:\n";
        for (const auto& extension : extensions)
        {
            //std::cout << "\t" << extension.extensionName << "\n";
            if (strcmp(extension.extensionName, extensionName) == 0)
            {
                return true;
            }
        }
        return false;
    }

    //Finds a device extensions
    bool findExtension(const char* extensionName, VkPhysicalDevice device)
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        for (const auto& extension : extensions)
        {
            if (strcmp(extension.extensionName, extensionName) == 0)
            {
                return true; 
            }
        }
        uint32_t dExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &dExtensionCount, nullptr);
        std::vector<VkExtensionProperties> dExtensions(dExtensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &dExtensionCount, dExtensions.data());
        for (const auto& extension : dExtensions)
        {
            if (strcmp(extension.extensionName, extensionName) == 0)
            {
                return true;
            }
        }
        return false;
    }

    //Check to see if the validation layer is supported. 
    bool checkValidationLayerSupport(std::vector<const char*> vec_validationlayers)
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        bool layerFound = false;

        for (const char* layerName : vec_validationlayers)
        {
            for (const VkLayerProperties& layerProperites : availableLayers)
            {
                if (strcmp(layerName, layerProperites.layerName) == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    //Reads chars from a file (used for a precompiled shader)
    std::vector<char> readFile(const std::string& fileName)
    {
        std::ifstream file(fileName, std::ios::ate | std::ios::binary);

        if (!file.good())
        {
            throw std::runtime_error("Couldn't open file!");
        }
        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer; 
    }

    //Returns a shader module that takes in the logical device and the shader code. 
    VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& vec_code)
    {
        VkShaderModuleCreateInfo createInfo{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
        createInfo.codeSize = vec_code.size(); 
        createInfo.pCode = reinterpret_cast<const uint32_t*>(vec_code.data()); 

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create shader module!"); 
        }
        return shaderModule; 
    }
}

