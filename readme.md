# Recursive ray tracer


With support for spheres and traingles, multiple light sources and anti-aliasing.

Affine transforms not yet implemented

### Input Format

Camera
\<Location of Eye in VCS\> (eg. 0 0 -10)
\<U vector in WCS\> (eg. 1 0 0)
\<V vector in WCS\>
\<N vector in WCS\>

Display
\<R\> (origin of display in WCS) (eg. 0 1 10)
(Extent of Display)\<Left\> \<Right\> \<Top\> \<Bottom\>) (WRT R)

Light
\<Ambient Light Intensity\> \<Background color R value\> \<Background color G value\> \<Background color B value\>

\<Number of Light sources\> (eg. 1)

\<Light source's X\> \<Light source's Y\> \<Light source's Z\> \<Light source's Intensity\>

and so on....

Spheres

\<Number of Spheres\>

\<X of center\> \<Y of center\> \<Z of center\> \<Radius\> \<R value\> \<G value\> \<B value\> \<Ka\> \<Kd\> \<Ks\> \<Krg\> \<Ktg\> \<Refractive index\> \<N for specular reflection\>

and so on....

Triangles

\<Number of Triangles\>

\<X of V1\> \<Y of V1\> \<Z of V1\> \<X of V2\> \<Y of V2\> \<Z of V2\> \<X of V3\> \<Y of V3\> \<Z of V3\> \<R value\> \<G value\> \<B value\> \<Ka\> \<Kd\> \<Ks\> \<Krg\> \<Ktg\> \<Refractive index\> \<N for specular reflection\>

and so on....

### Compiling
    make compile
    
### Running
    either         ./main <input file>
    or             make input=<input file> run
    
    
