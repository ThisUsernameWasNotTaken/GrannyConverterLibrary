use std::ffi::CString;
use std::ffi::CStr;
use std::ffi::c_char;
pub fn extractFbxWithGrannyConverter(baseFilepath: String, list: Vec<String>) {
    unsafe {
        //     // let result = extractFbx(&extractPath.into_os_string().into_string().unwrap(), list);
        //     // let result = add_numbers(22, 33);
        //     // print!("{}", result);
        //     let result = test(CString::new("test string").unwrap().as_ptr());
        //     // let result: &str = &String::from_utf8(Vec::from(result.as_ref().unwrap().to_le_bytes())).unwrap();
        //     let result = CStr::from_ptr(result);
        //     let result = result.to_str().unwrap();
        //     println!("{}", result);
        //
        // let inputArr = [
        //     ptr_from("test").unwrap().as_ptr(),
        //     CString::new("string").unwrap().as_ptr(),
        //     //         CString::new("test string").unwrap().as_ptr(),
        //     //         CString::new("testo").unwrap().as_ptr(),
        // ];
        // let baseFilepath = CString::new(baseFilepath.as_str()).unwrap().as_ptr();
        // extractFbx(baseFilepath, &inputArr);
        let inputArr = list.iter().map(|x| CString::new(x)).as_slice();
        // .as_slice().iter().map(|| CString::new);
        let baseFilepath = CString::new(baseFilepath.as_str()).unwrap().as_ptr();
        extractFbx(baseFilepath, &inputArr);
    }
}

unsafe fn string_slice_from(raw: *const c_char) -> String {
    CStr::from_ptr(raw).to_str().unwrap().to_string()
}

extern "C" {
    fn add_numbers(a: i32, b: i32) -> i32;
    fn test(a: *const c_char) -> *const c_char;
    fn testArr(a: &[*const c_char]) -> *const c_char;
    fn extractFbx(baseFilepath: *const c_char, list: &[*const c_char]) -> i32;
}