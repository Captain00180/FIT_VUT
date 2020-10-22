/*!
 * @file
 * @brief This file contains implementation of phong rendering method
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/phongMethod.hpp>
#include <student/bunny.hpp>

/** \addtogroup shader_side 06. Implementace vertex/fragment shaderu phongovy metody
 * Vašim úkolem ve vertex a fragment shaderu je transformovat trojúhelníky pomocí view a projekční matice a spočítat phongův osvětlovací model.
 * Vašim úkolem také je správně vypočítat procedurální barvu.
 * Následující obrázek zobrazuje shadery v různém stupni implementace.
 * Horní řáděk zobrazuje procedurální texturu.
 * Prostřední řádek zobrazuje model králička s nanesenou texturou, ale bez použití transformačních matic.
 * Dolní řádek zobrazuje model po použítí transformačních matic.
 *
 * \image html images/texture.svg "Vypočet procedurální textury." width=1000
 *
 * 
 *
 *
 *
 * @{
 */


float     max_0                 (float num)
{
    if(num < 0)
    {
        return 0;
    }
    return num;
}

/**
 * @brief This function represents vertex shader of phong method.
 *
 * @param outVertex output vertex
 * @param inVertex input vertex
 * @param uniforms uniform variables
 */
void phong_VS(OutVertex&outVertex,InVertex const&inVertex,Uniforms const&uniforms){
  /// \todo Naimplementujte vertex shader, který transformuje vstupní vrcholy do
  /// clip-space.<br>
  /// <b>Vstupy:</b><br>
  /// Vstupní vrchol by měl v nultém atributu obsahovat pozici vrcholu ve
  /// world-space (vec3) a v prvním
  /// atributu obsahovat normálu vrcholu ve world-space (vec3).<br>
  /// <b>Výstupy:</b><br>
  /// Výstupní vrchol by měl v nultém atributu obsahovat pozici vrcholu (vec3)
  /// ve world-space a v prvním
  /// atributu obsahovat normálu vrcholu ve world-space (vec3).
  /// Výstupní vrchol obsahuje pozici a normálu vrcholu proto, že chceme počítat
  /// osvětlení ve world-space ve fragment shaderu.<br>
  /// <b>Uniformy:</b><br>
  /// Vertex shader by měl pro transformaci využít uniformní proměnné obsahující
  /// view a projekční matici.
  /// View matici čtěte z nulté uniformní proměnné a projekční matici
  /// čtěte z první uniformní proměnné.
  /// <br>
  /// Využijte vektorové a maticové funkce.
  /// Nepředávajte si data do shaderu pomocí globálních proměnných.
  /// Vrchol v clip-space by měl být zapsán do proměnné gl_Position ve výstupní
  /// struktuře.
  /// \image html images/vertex_shader_tasks.svg "Vizualizace vstupů a výstupů vertex shaderu" width=1000


  // Position
  outVertex.attributes[0].v3 = inVertex.attributes[0].v3;
  // Normal
  outVertex.attributes[1].v3 = inVertex.attributes[1].v3;

  auto pos = inVertex.attributes[0].v3;
  auto norm = inVertex.attributes[1].v3;

  auto vm = uniforms.uniform[0].m4;
  auto pm = uniforms.uniform[1].m4;

  auto vpm = pm * vm;

  outVertex.gl_Position = vpm * glm::vec4(pos, 1.f);


}

/**
 * @brief This function represents fragment shader of phong method.
 *
 * @param outFragment output fragment
 * @param inFragment input fragment
 * @param uniforms uniform variables
 */
void phong_FS(OutFragment&outFragment,InFragment const&inFragment,Uniforms const&uniforms){
  /// \todo Naimplementujte fragment shader, který počítá phongův osvětlovací
  /// model s phongovým stínováním.<br>
  /// <b>Vstup:</b><br>
  /// Vstupní fragment by měl v nultém fragment atributu obsahovat
  /// interpolovanou pozici ve world-space a v prvním
  /// fragment atributu obsahovat interpolovanou normálu ve world-space.<br>
  /// <b>Výstup:</b><br>
  /// Barvu zapište do proměnné gl_FragColor ve výstupní struktuře.<br>
  /// <b>Uniformy:</b><br>
  /// Pozici kamery přečtěte z uniformní 3 a pozici
  /// světla přečtěte z uniformní 2.
  /// <br>
  /// <br>
  /// Dejte si pozor na velikost normálového vektoru, při lineární interpolaci v
  /// rasterizaci může dojít ke zkrácení.
  /// Zapište barvu do proměnné gl_FragColor ve výstupní struktuře.
  /// Shininess faktor nastavte na 40.f
  /// <br>
  /// <br>
  /// Difuzní barva materiálu (textura) by měla být procedurálně generována.
  /// Textura je složena zde dvou částí: sinusové pruhy a bílý sněhový poprašek.
  /// Textura je zkombinována z těchto dvou částí podle sklonu normály.
  /// V případě, že normála směřuje kolmo vzhůru je textura čistě bílá.
  /// V případě, že normála směřuje vodorovně nebo dolů je textura složena ze sinusových pruhů.
  /// Bílá textura a textura sinusových pruhů je lineráně míchana pomocí interpolačního parameteru t.
  /// Interpolační parameter t spočtěte z y komponenty normály pomocí t = y*y (samozřejmě s ohledem na negativní čísla).
  /// 
  /// \image html images/texture_combination.svg "Vizualizace kombinace textury sinusových pruhů a sněhového poprašku." width=600
  /// <br>
  /// <br>
  /// Sinusové pruhy jsou naneseny v rovině xy pomocí planárního nanášení textur, viz následující obrázek:
  /// \image html images/texture_plane.svg "Vizualizace nanášení textury sinusových pruhů." width=600
  ///
  /// Sinusová textura obsahuje 10 pruhů 5 zelených (0,0.5,0) a pět žlutých (1,1,0).
  /// Pruhy mají stejnou tloušku.
  /// Textura má velikost 1x1 a opakuje se (platí i pro záporné souřadnice).
  /// Pruhy jsou zvlněny pomocí funkce sinus.
  /// Amplituda funkce sinus je 0.1.
  /// Perioda je nastavena na \f$ \frac{2 \cdot \pi}{10} \f$.
  /// Výchylku pruhu lze tedy spočítat jako \f$ \frac{sin(y \cdot 10)}{10} \f$
  /// Tvorba textury je znázorněna na následujícím obrázku:
  ///
  /// \image html images/stripes_texture.svg "Vizualizace tvorby sinusové textury" width=600
  /// 
  /// 
  /// Spekulární barvu materiálu nastavte na čistou bílou.
  /// Barvu světla nastavte na bílou.
  /// Nepoužívejte ambientní světlo.<br>
  ///
  /// \image html images/fragment_shader_tasks.svg "Vizualizace výpočtu ve fragment shaderu" width=1000

  glm::vec4 color_snow = glm::vec4(1,1,1,1);
  glm::vec4 color_green = glm::vec4(0,0.5,0,1);
  glm::vec4 color_yellow = glm::vec4(1,1,0,1);
  glm::vec4 color_final = glm::vec4(1,1,1,1);
  auto normal = inFragment.attributes[1].v3;
  normal = glm::normalize(normal);


    // Normal of the fragment is not vertical - set color to texture (default is white snow)
  if (!(normal[0] == 0 && normal[1] > 0 && normal[2] == 0 ))
  {

      // Set color to the texture color
      float variance = (sinf(inFragment.attributes[0].v3.y * 10)) / 10;

      auto x_coord = inFragment.attributes[0].v3.x + variance;
      int decimal = static_cast<int>(x_coord * 10);
      // Positive number
      if(x_coord > 0)
      {
          // Odd - yellow | even - green
          if(decimal % 2)
          {
              color_final = color_yellow;
          } else{
              color_final = color_green;
          }
      }
      // Negative number
      else
      {
          //Odd - green | even - yellow
          if (decimal % 2)
          {
              color_final = color_green;
          } else{
              color_final = color_yellow;
          }
      }

      // Set color to the lineaer combination of snow and texture
      if(normal[1] >= 0) {
          float t = normal[1] * normal[1];
          color_final = t * color_snow  + (1 - t) * color_final;
      }
  }

    // Phong shading

  auto position = glm::vec3(inFragment.attributes[0].v3);
  auto light = uniforms.uniform[2].v3;
  light = light - position;
  auto camera = uniforms.uniform[3].v3;
  camera = camera - position;

  position = glm::normalize(position);
  light = glm::normalize(light);
  camera = glm::normalize(camera);

  auto diffuse_factor = glm::dot(light, normal);
  diffuse_factor = max_0(diffuse_factor);

  glm::vec4 Id = diffuse_factor * color_final;

  // Calculate specular lighting
  if(diffuse_factor > 0)
  {
      auto dot_n_l = glm::dot(normal, light);
      dot_n_l = max_0(dot_n_l);

      auto r_vec = 2 * dot_n_l * normal - light;

      auto Sf = glm::dot(camera, r_vec);
      Sf = max_0(Sf);
      Sf = powf(Sf, 40.f);


      Id = Id + Sf;
  }

  // Save final color to outfragment
  outFragment.gl_FragColor = Id;


  for(int i = 0; i < 4; ++i)
  {
      outFragment.gl_FragColor[i] = std::min(1.f, outFragment.gl_FragColor[i]);

  }

}

/// @}

/** \addtogroup cpu_side 07. Implementace vykreslení králička s phongovým osvětlovacím modelem.
 * Vaším úkolem je využít naimplementovanou grafickou kartu a vykreslit králička s phongovým osvětlovacím modelem a stínováním a procedurální texturou.
 * @{
 */


/**
 * @brief Constructoro f phong method
 */
PhongMethod::PhongMethod(){
/// \todo Doprogramujte inicializační funkci.
/// Zde byste měli vytvořit buffery na GPU, nahrát data do bufferů, vytvořit
/// vertex puller a správně jej nakonfigurovat, vytvořit program, připojit k
/// němu shadery a nastavit atributy, které se posílají mezi vs a fs.
/// Do bufferů nahrajte vrcholy králička (pozice, normály) a indexy na vrcholy
/// ze souboru \ref bunny.hpp.
/// Shader program by měl odkazovat na funkce/shadery phong_VS a phong_FS.
/// V konfiguraci vertex pulleru nastavte dvě čtecí hlavy.
/// Jednu pro pozice vrcholů a druhou pro normály vrcholů.
/// Nultý vertex/fragment atribut by měl obsahovat pozici vertexu.
/// První vertex/fragment atribut by měl obsahovat normálu vertexu.
/// Nastavte, které atributy (jaký typ) se posílají z vertex shaderu do fragment shaderu.
/// <b>Seznam funkcí, které jistě využijete:</b>
///  - gpu.createBuffer()
///  - gpu.setBufferData()
///  - gpu.createVertexPuller()
///  - gpu.setVertexPullerIndexing()
///  - gpu.setVertexPullerHead()
///  - gpu.enableVertexPullerHead()
///  - gpu.createProgram()
///  - gpu.attachShaders()
///  - gpu.setVS2FSType()

    //Index buffer
    idb = gpu.createBuffer(sizeof(VertexIndex) * 3 * 2092);
    gpu.setBufferData(idb, 0, 2092 * 3 * sizeof(VertexIndex), bunnyIndices);
    //Vertex buffer
    vb = gpu.createBuffer(1048 * sizeof(BunnyVertex));
    gpu.setBufferData(vb, 0, 1048 * sizeof(BunnyVertex), bunnyVertices);

    vp = gpu.createVertexPuller();
    gpu.setVertexPullerIndexing(vp, IndexType::UINT32, idb);

    gpu.setVertexPullerHead(vp, 0, AttributeType::VEC3, sizeof(BunnyVertex) ,0, vb);
    gpu.enableVertexPullerHead(vp, 0);
    gpu.setVertexPullerHead(vp, 1, AttributeType::VEC3, sizeof(BunnyVertex) , sizeof(BunnyVertex::position), vb);
    gpu.enableVertexPullerHead(vp, 1);

    prg = gpu.createProgram();
    gpu.attachShaders(prg, phong_VS, phong_FS);
    gpu.setVS2FSType(prg, 0, AttributeType::VEC3);
    gpu.setVS2FSType(prg, 1, AttributeType::VEC3);

}


/**
 * @brief This function draws phong method.
 *
 * @param proj projection matrix
 * @param view view matrix
 * @param light light position
 * @param camera camera position
 */
void PhongMethod::onDraw(glm::mat4 const&proj,glm::mat4 const&view,glm::vec3 const&light,glm::vec3 const&camera){

/// \todo Doprogramujte kreslící funkci.
/// Zde byste měli aktivovat shader program, aktivovat vertex puller, nahrát
/// data do uniformních proměnných a
/// vykreslit trojúhelníky pomocí funkce \ref GPU::drawTriangles.
/// Data pro uniformní proměnné naleznete v parametrech této funkce.
/// <b>Seznam funkcí, které jistě využijete:</b>
///  - gpu.bindVertexPuller()
///  - gpu.useProgram()
///  - gpu.programUniformMatrix4f()
///  - gpu.programUniform3f      ()
///  - gpu.drawTriangles()
///  - gpu.unbindVertexPuller()

  gpu.clear(.5f,.5f,.5f,1.f);

  gpu.bindVertexPuller(vp);
  gpu.useProgram(prg);
  gpu.programUniformMatrix4f(prg, 0, view);
  gpu.programUniformMatrix4f(prg, 1, proj);
  gpu.programUniform3f(prg, 2, light);
  gpu.programUniform3f(prg, 3, camera);

  gpu.drawTriangles(2092 * 3);
  gpu.unbindVertexPuller();

}

/**
 * @brief Destructor of phong method.
 */
PhongMethod::~PhongMethod(){
  ///\todo Zde uvolněte alokované zdroje
  /// <b>Seznam funkcí</b>
  ///  - gpu.deleteProgram()
  ///  - gpu.deleteVertexPuller()
  ///  - gpu.deleteBuffer()

  gpu.deleteProgram(prg);
  gpu.deleteVertexPuller(vp);
  gpu.deleteBuffer(idb);
  gpu.deleteBuffer(vb);

}

/// @}
