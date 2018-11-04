{-# LANGUAGE ForeignFunctionInterface #-}

module Lib (someFunc) where

import Foreign.C
import Foreign.Ptr (Ptr, nullPtr)
import Foreign.Marshal.Alloc

-- foreign import ccall "time" c_time :: Ptr a -> IO CTime
-- someFunc :: IO CTime
-- someFunc = c_time nullPtr

data BPFModule = BPFModule
type BPFModulePtr = Ptr BPFModule

-- TODO: Should the return type of this function be IO BPFModulePtr or without IO? Does compiling bpf code count as side effect?
foreign import ccall "bpf_module_create_c_from_string" createModuleFromString :: CString -> CUInt -> CString -> CInt -> IO BPFModulePtr
foreign import ccall "bpf_module_destroy" destroyModule :: BPFModulePtr -> IO ()
-- foreign import ccall "bpf_prog_load" loadProg ::
-- foreign import ccall "bpf_function_start"
-- foreign import ccall "bpf_function_size"
-- foreign import ccall "bpf_module_license"
-- foreign import ccall "bpf_module_kern_version"
-- foreign import ccall "bpf_attach_kprobe"

-- TODO: How do I actually put a newline like \"Hello, World\n\"?
bpf_text = "int kprobe__sys_clone(void *ctx) { bpf_trace_printk(\"Hello, World!\"); return 0; }"


-- TODO: Should bpf_str be explicitly free'd? as in this single function example
-- someFunc :: IO ()
-- someFunc = do
--   bpf_str <- newCString bpf_text
--   hs_str <- peekCString bpf_str
--   putStrLn hs_str
--   bpf_mod <- createModuleFromString bpf_str 0 nullPtr 0
--   destroyModule bpf_mod
--   free bpf_str

createBPF :: String -> IO BPFModulePtr
createBPF bpf_text = do
  bpf_str <- newCString bpf_text
  createModuleFromString bpf_str 0 nullPtr 0

-- TODO: Does it matter if the IO BPFModulePtr get bound outside of function or inside function?
-- loadBPF :: IO BPFModulePtr ->

someFunc :: IO ()
someFunc = do
  bpf_mod <- createBPF bpf_text
  destroyModule bpf_mod
