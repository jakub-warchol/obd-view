varying highp vec2 qt_TexCoord0;
uniform sampler2D src;

void main(void)
{
    lowp vec3 black = vec3(0., 0., 0.);
    highp vec4 col  = texture2D(src, qt_TexCoord0.xy);
    if(col.rgb != black) { // if color is white
        col.rgb = black;  // then set black
    }

    gl_FragColor = col;
}
