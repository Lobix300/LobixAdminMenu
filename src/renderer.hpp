#pragma once
#include "common.hpp"
#include <set>

typedef void(*PresentCallback)(void*);

class StateSaver
{
	// Public functions
	public:
		StateSaver();
		~StateSaver();

		bool saveCurrentState(ID3D11DeviceContext* pContext);
		bool restoreSavedState();
		void releaseSavedState();

	// Internal data
	private:
		bool						m_savedState;
		D3D_FEATURE_LEVEL			m_featureLevel;
		ID3D11DeviceContext* m_pContext;
		D3D11_PRIMITIVE_TOPOLOGY	m_primitiveTopology;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11BlendState* m_pBlendState;
		FLOAT						m_blendFactor[4];
		UINT						m_sampleMask;
		ID3D11DepthStencilState* m_pDepthStencilState;
		UINT						m_stencilRef;
		ID3D11RasterizerState* m_pRasterizerState;
		ID3D11ShaderResourceView* m_pPSSRV;
		ID3D11SamplerState* m_pSamplerState;
		ID3D11VertexShader* m_pVS;
		ID3D11ClassInstance* m_pVSClassInstances[256];
		UINT						m_numVSClassInstances;
		ID3D11Buffer* m_pVSConstantBuffer;
		ID3D11GeometryShader* m_pGS;
		ID3D11ClassInstance* m_pGSClassInstances[256];
		UINT						m_numGSClassInstances;
		ID3D11Buffer* m_pGSConstantBuffer;
		ID3D11ShaderResourceView* m_pGSSRV;
		ID3D11PixelShader* m_pPS;
		ID3D11ClassInstance* m_pPSClassInstances[256];
		UINT						m_numPSClassInstances;
		ID3D11HullShader* m_pHS;
		ID3D11ClassInstance* m_pHSClassInstances[256];
		UINT						m_numHSClassInstances;
		ID3D11DomainShader* m_pDS;
		ID3D11ClassInstance* m_pDSClassInstances[256];
		UINT						m_numDSClassInstances;
		ID3D11Buffer* m_pVB;
		UINT						m_vertexStride;
		UINT						m_vertexOffset;
		ID3D11Buffer* m_pIndexBuffer;
		DXGI_FORMAT					m_indexFormat;
		UINT						m_indexOffset;

		StateSaver(const StateSaver&);
};

namespace big
{
	using dx_callback = std::function<void()>;
	using wndproc_callback = std::function<void(HWND, UINT, WPARAM, LPARAM)>;

	class renderer final
	{
	public:
		explicit renderer();
		~renderer();

		/**
		 * @brief Add a callback function to draw your ImGui content in
		 * 
		 * @param callback Function
		 * @param priority The higher the priority the value the later it gets drawn on top
		 * @return true 
		 * @return false 
		 */
		bool add_dx_callback(dx_callback callback, std::uint32_t priority);
		/**
		 * @brief Add a callback function on wndproc
		 * 
		 * @param callback Function
		 */
		void add_wndproc_callback(wndproc_callback callback);

		void on_present();

		void rescale(float rel_size);

		void pre_reset();
		void post_reset();

		bool add_callback(PresentCallback callback) { return m_present_callbacks.insert(callback).second; }
		bool remove_callback(PresentCallback callback) { return m_present_callbacks.erase(callback) != 0; }

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
        static void new_frame();
        static void end_frame();

		IDXGISwapChain* m_dxgi_swapchain;
		ID3D11Device* m_d3d_device;
		ID3D11DeviceContext* m_d3d_device_context;

		std::map<std::uint32_t, dx_callback> m_dx_callbacks;
		std::vector<wndproc_callback> m_wndproc_callbacks;

		std::set<PresentCallback> m_present_callbacks;
		std::unique_ptr<StateSaver> m_stateSaver;
		bool m_restoreState = false;
		
	};

	inline renderer* g_renderer{};
}
