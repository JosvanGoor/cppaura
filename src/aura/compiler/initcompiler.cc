#include "compiler.ih"

void Compiler::init_compiler(LocalCompiler *compiler, FunctionType type)
{
    compiler->function = nullptr;
    compiler->type = type;
    compiler->scope_depth = 0;
    compiler->function = d_vm->allocate_object<ObjFunction>(d_vm);
    compiler->locals.push_back({{}, 0});
    
    switch(type)
    {
        case FunctionType::INITIALIZER: [[fallthrough]];
        case FunctionType::METHOD:
            compiler->locals[0].name.start = "this";
            compiler->locals[0].name.length = 4;
            break;
        
        default: break;
    }
    
    compiler->enclosing = d_compiler;
    d_compiler = compiler;

    switch(type)
    {
        case FunctionType::FUNCTION:    [[fallthrough]];
        case FunctionType::INITIALIZER: [[fallthrough]];
        case FunctionType::METHOD:
            d_compiler->function->name = d_vm->copy_string(d_previous.start, d_previous.length);
            break;
        
        case FunctionType::LAMBDA:
            {
                stringstream ss;
                ss << "lambda @ " << reinterpret_cast<void*>(d_compiler->function);
                string name = ss.str();
                d_compiler->function->name = d_vm->copy_string(name.c_str(), name.size());
                break;
            }
        case FunctionType::SCRIPT:
            break;
    }    
    
    // if (type != FunctionType::SCRIPT && type != FunctionType::LAMBDA)
    //     d_compiler->function->name = d_vm->copy_string(d_previous.start, d_previous.length);
}