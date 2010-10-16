#ifndef GRAPHBUILDERADAPTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define GRAPHBUILDERADAPTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#include <map>
#include <stack>
#include "anchordict.h"
#include "eventhandler.h"
#include "graphbuilder.h"

namespace YAML
{
  class GraphBuilderAdapter : public EventHandler
  {
  public:
    GraphBuilderAdapter(GraphBuilderInterface& builder)
    : m_builder(builder), m_pRootNode(NULL), m_pKeyNode(NULL)
    {
    }
    
    virtual void OnDocumentStart(const Mark& mark) {(void)mark;}
    virtual void OnDocumentEnd() {}
    
    virtual void OnNull(const std::string& tag, anchor_t anchor);
    virtual void OnAlias(const Mark& mark, anchor_t anchor);
    virtual void OnScalar(const Mark& mark, const std::string& tag, anchor_t anchor, const std::string& value);
    
    virtual void OnSequenceStart(const Mark& mark, const std::string& tag, anchor_t anchor);
    virtual void OnSequenceEnd();
    
    virtual void OnMapStart(const Mark& mark, const std::string& tag, anchor_t anchor);
    virtual void OnMapEnd();
    
    void *RootNode() const {return m_pRootNode;}
  
  private:
    struct ContainerFrame
    {
      ContainerFrame(void *pSequence)
      : pContainer(pSequence), pPrevKeyNode(&sequenceMarker)
      {}
      ContainerFrame(void *pMap, void* pPrevKeyNode)
      : pContainer(pMap), pPrevKeyNode(pPrevKeyNode)
      {}
      
      void *pContainer;
      void *pPrevKeyNode;
      
      bool isMap() const {return pPrevKeyNode != &sequenceMarker;}
    
    private:
      static int sequenceMarker;
    };
    typedef std::stack<ContainerFrame> ContainerStack;
    typedef AnchorDict<void*> AnchorMap;
    
    GraphBuilderInterface& m_builder;
    ContainerStack m_containers;
    AnchorMap m_anchors;
    void *m_pRootNode;
    void *m_pKeyNode;
    
    void *GetCurrentParent() const;
    void RegisterAnchor(anchor_t anchor, void *pNode);
    void DispositionNode(void *pNode);
  };
}

#endif // GRAPHBUILDERADAPTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66