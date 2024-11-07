#include <Windows.h>
#include <msctf.h>
#include <vector>
#include <string>
#include <iostream>

int main() {
    // Initialize COM
    CoInitialize(NULL);

    // Create a TSF Thread Manager
    ITfThreadMgr *pThreadMgr = NULL;
    CoCreateInstance(CLSID_TF_ThreadMgr, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pThreadMgr) );

    if (!pThreadMgr) {
        std::cerr << "Failed to create TSF Thread Manager." << std::endl;
        return 1;
    }

    // Activate the TSF manager
    TfClientId clientId;
    pThreadMgr->Activate(&clientId);

    // Create Document Manager
    ITfDocumentMgr *pDocMgr = NULL;
    pThreadMgr->CreateDocumentMgr(&pDocMgr);

    ITfContext *pContext = NULL;
    if (pDocMgr->CreateContext(clientId, 0, NULL, &pContext, NULL) != S_OK) {
        std::cerr << "Failed to create edit context." << std::endl;
        return 1;
    }

    // Set the edit context as the top context in the document manager
    pDocMgr->Push(pContext);

        std::vector<std::wstring> searchList = {L"hello", L"world", L"example"};

    class MyEditSession : public ITfEditSession
    {
    private:
        std::vector<std::wstring> m_searchList;
        ITfContext *m_pContext;

    public:
        MyEditSession(const std::vector<std::wstring> &searchList, ITfContext *pContext) : m_searchList(searchList), m_pContext(pContext)
        {}

        HRESULT STDMETHODCALLTYPE DoEditSession(TfEditCookie ec)
        {
            ITfRange *pRange;
            if (FAILED(m_pContext->GetStart(ec, &pRange))) {
                return E_FAIL;
            }

            WCHAR buffer[256];
            ULONG cch;
            if (SUCCEEDED(pRange->GetText(ec, 0, buffer, ARRAYSIZE(buffer) - 1, &cch))) {
                std::wstring inputText(buffer, cch);

                // Search for a match
                for (const auto &str: m_searchList) {
                    if (inputText == str) {
                        pRange->SetText(ec, 0, str.c_str(), str.length());
                        break;
                    }
                }
            }
            return S_OK;
        }

        ULONG STDMETHODCALLTYPE AddRef() override
        { return 1; }

        ULONG STDMETHODCALLTYPE Release() override
        { return 1; }

        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObj) override
        {
            if (riid == IID_IUnknown || riid == IID_ITfEditSession) {
                *ppvObj = this;
                return S_OK;
            }
            *ppvObj = NULL;
            return E_NOINTERFACE;
        }
    };

    auto CaptureAndReplaceText = [&](ITfContext *context, const std::vector<std::wstring>& searchList) {
        // Start an edit session
        ITfEditSession *pEditSession;
        HRESULT hr = context->RequestEditSession(clientId, new MyEditSession(searchList, pContext), TF_ES_READWRITE | TF_ES_SYNC, &hr);

        if (FAILED(hr)) {
            std::cerr << "Edit session failed." << std::endl;
        }
    };

    CaptureAndReplaceText(pContext, searchList);

    // Clean up and release resources
    pContext->Release();
    pDocMgr->Pop(TF_POPF_ALL);
    pDocMgr->Release();
    pThreadMgr->Deactivate();
    pThreadMgr->Release();

    CoUninitialize();
    return 0;
}
