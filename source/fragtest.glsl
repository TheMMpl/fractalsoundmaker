uniform vec2 res;

void main()
{
    vec2 pos=gl_FragCoord.xy-(res.xy*0.5);
    if(pos.x>0.5)
    {
        gl_FragColor = vec4(0.3, 0.0, 0.3, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}