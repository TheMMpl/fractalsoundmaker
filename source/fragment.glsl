#version 400 compatibility

uniform vec2 res;
uniform int fractalid;

vec2 cmult(vec2 v,vec2 w)
{
    vec2 res;
    res.x=v.x*w.x-v.y*w.y;
    res.y=2*v.x*w.y;
    return res;
}

vec2 mandlebrot(vec2 rec,vec2 point)
{
    return cmult(rec,rec)+point;
}

vec2 sfx(vec2 rec,vec2 point)
{
    vec2 c=vec2(point.x*point.x,point.y*point.y);
    return rec*(length(rec)*length(rec))-cmult(rec,c);
}

void main()
{
    vec2 pos=gl_FragCoord.xy-(res.xy*0.5);
    gl_FragColor=vec4(0.0,0.0,0.0,1.0);
    vec2 rec=pos.xy/200;
    pos=pos.xy/200;
    for(int i=0;i<200;i++)
    {
        if(fractalid==0)rec=mandlebrot(rec,pos);
        else rec=sfx(rec,pos);
        if(length(rec)>1000)
        gl_FragColor=vec4(1.0,1.0,1.0,1.0);
    }
}