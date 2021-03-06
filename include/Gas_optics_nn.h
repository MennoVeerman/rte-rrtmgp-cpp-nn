#ifndef GAS_OPTICS_NN_H
#define GAS_OPTICS_NN_H

#include <string>
#include "Array.h"
#include "Netcdf_interface.h"
#include <Network.h>
#include "Gas_optics.h"

#define restrict __restrict__
// Forward declarations.
template<typename TF> class Optical_props;
template<typename TF> class Optical_props_arry;
template<typename TF> class Gas_concs;
template<typename TF> class Source_func_lw;

template<typename TF>
class Gas_optics_nn : public Gas_optics<TF>
{
    public:
        // Constructor for longwave variant.
        Gas_optics_nn(
                const Array<std::string,1>& gas_names,
                const Array<int,2>& band2gpt,
                const Array<TF,2>& band_lims_wavenum,
                const std::string& file_name_weights,
                Netcdf_file& input_nc);

        // Constructor for shortwave variant.
        Gas_optics_nn(
                const Array<std::string,1>& gas_names,
                const Array<int,2>& band2gpt,
                const Array<TF,2>& band_lims_wavenum,
                const Array<TF,1>& solar_src_quiet,
                const Array<TF,1>& solar_src_facular,
                const Array<TF,1>& solar_src_sunspot,
                const TF tsi_default,
                const TF mg_default,
                const TF sb_default,
                const std::string& file_name_weights,
                Netcdf_file& input_nc);

        // Longwave variant.
        void gas_optics(
                const Array<TF,2>& play,
                const Array<TF,2>& plev,
                const Array<TF,2>& tlay,
                const Array<TF,1>& tsfc,
                const Gas_concs<TF>& gas_desc,
                std::unique_ptr<Optical_props_arry<TF>>& optical_props,
                Source_func_lw<TF>& sources,
                const Array<TF,2>& col_dry,
                const Array<TF,2>& tlev) const;

        // Shortwave variant.
        void gas_optics(
                const Array<TF,2>& play,
                const Array<TF,2>& plev,
                const Array<TF,2>& tlay,
                const Gas_concs<TF>& gas_desc,
                std::unique_ptr<Optical_props_arry<TF>>& optical_props,
                Array<TF,2>& toa_src,
                const Array<TF,2>& col_dry) const;

        bool source_is_internal() const {return 0;}
        bool source_is_external() const {return 0;}

        TF get_press_ref_min() const {return TF(0.);}
        TF get_press_ref_max() const {return TF(0.);}

        TF get_temp_min() const {return TF(0.);}
        TF get_temp_max() const {return TF(0.);}

        TF get_tsi() const;

    private:
        const TF press_ref_trop = 9948.431564193395; //network is trained on this boundary, so it is hardcoded
        Array<std::string,1> gas_names;

        void set_solar_variability(
            const TF md_index, const TF sb_index);

        void initialize_networks(
            const std::string& wgth_file,
            Netcdf_file& input_nc);

        void compute_tau_ssa_nn(
                const Network& nw_ssa,
                const Network& nw_tsw,
                const int ncol, const int nlay, const int ngpt,
                const int nband, const int idx_tropo,
                const TF* restrict const play,
                const TF* restrict const plev,
                const TF* restrict const tlay,
                const Gas_concs<TF>& gas_desc,
                std::unique_ptr<Optical_props_arry<TF>>& optical_props,
                const bool lower_atm, const bool upper_atm) const;

        void compute_tau_sources_nn(
                const Network& nw_tlw,
                const Network& nw_plk,
                const int ncol, const int nlay, const int ngpt,
                const int nband, const int idx_tropo,
                const TF* restrict const play, 
                const TF* restrict const plev,
                const TF* restrict const tlay, 
                const TF* restrict const tlev,
                const Gas_concs<TF>& gas_desc,
                Source_func_lw<TF>& sources,
                std::unique_ptr<Optical_props_arry<TF>>& optical_props,
                const bool lower_atm, const bool upper_atm) const;

        void lay2sfc_factor(
                const Array<TF,2>& tlay,
                const Array<TF,1>& tsfc,
                Source_func_lw<TF>& sources,
                const int ncol,
                const int nlay,
                const int nband) const;

        Array<TF,1> solar_source_quiet;
        Array<TF,1> solar_source_facular;
        Array<TF,1> solar_source_sunspot;
        Array<TF,1> solar_source;

        Network tsw_network;
        Network ssa_network;
        Network tlw_network;
        Network plk_network;

        int n_layers;
        int n_layer1;
        int n_layer2;
        int n_layer3;
        int n_o3;

        int idx_tropo;
        bool lower_atm;
        bool upper_atm;
};
#endif
