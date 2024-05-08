#version 330 core

void main()
{             
    // gl_FragDepth = gl_FragCoord.z;// 取消那行的注释，来显式设置深度，但是这个（指注释掉那行之后）是更有效率的，因为底层无论如何都会默认去设置深度缓冲。
}