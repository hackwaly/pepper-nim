proc log(str: cstring) {.importc: "PostMessage".}

log("hello");