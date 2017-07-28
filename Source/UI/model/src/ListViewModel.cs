using System;
using System.Collections;
using System.Collections.Generic;
using Windows.Foundation.Collections;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace ListViewModel
{
    public sealed class DataTemplateModel
    {
        //
        // common placeholders
        //
        public string Data0 { get; set; }
        public string Data1 { get; set; }
        public string Data2 { get; set; }
        public string Data3 { get; set; }
        public string Data4 { get; set; }
        public string Data5 { get; set; }
        public string Data6 { get; set; }
        public string Data7 { get; set; }
        public string Data8 { get; set; }
        public string Data9 { get; set; }

        //
        // common property names
        //
        public string Data { get; set; }
        public string Name { get; set; }
        public string Title { get; set; }
        public string First { get; set; }
        public string Middle { get; set; }
        public string Last { get; set; }
        public string Id { get; set; }
        public string Text { get; set; }
        public string Image { get; set; }
        public string Subtitle { get; set; }
        public string Description { get; set; }
        public string Street { get; set; }
        public string City { get; set; }
        public string State { get; set; }
        public string Postcode { get; set; }
        public string Email { get; set; }
        public string UserName { get; set; }

        private HashSet<string> properties = new HashSet<string>();

        public IDictionary<string, string> GetProperties()
        {
            var dict = new Dictionary<string, string>();
            foreach (var name in properties)
            {
                dict.Add(name, GetProperty(name));
            }
            return dict;
        }

        public string GetProperty(string name)
        {
            string key = name.ToLower();
            switch (key)
            {
                case "data0": return Data0;
                case "data1": return Data1;
                case "data2": return Data2;
                case "data3": return Data3;
                case "data4": return Data4;
                case "data5": return Data5;
                case "data6": return Data6;
                case "data7": return Data7;
                case "data8": return Data8;
                case "data9": return Data9;
                case "data":  return Data;
                case "name":  return Name;
                case "title": return Title;
                case "first": return First;
                case "last":  return Last;
                case "middle": return Middle;
                case "id": return Id;
                case "text": return Text;
                case "image": return Image;
                case "subtitle": return Subtitle;
                case "description": return Description;
                case "street": return Street;
                case "city": return City;
                case "state": return State;
                case "postcode": return Postcode;
                case "email": return Email;
                case "username": return UserName;
            }
            return null;
        }

        public bool SetProperty(string name, string data)
        {
            string key = name.ToLower();

            //
            // Record what's updated
            //
            properties.Add(name);

            switch (key)
            {
                case "data0": Data0 = data; return true;
                case "data1": Data1 = data; return true;
                case "data2": Data2 = data; return true;
                case "data3": Data3 = data; return true;
                case "data4": Data4 = data; return true;
                case "data5": Data5 = data; return true;
                case "data6": Data6 = data; return true;
                case "data7": Data7 = data; return true;
                case "data8": Data8 = data; return true;
                case "data9": Data9 = data; return true;
                case "data": Data = data; return true;
                case "name": Name = data; return true;
                case "title": Title = data; return true;
                case "first": First = data; return true;
                case "last": Last = data; return true;
                case "middle": Middle = data; return true;
                case "id": Id = data; return true;
                case "text": Text = data; return true;
                case "image": Image = data; return true;
                case "subtitle": Subtitle = data; return true;
                case "description": Description = data; return true;
                case "street": Street = data; return true;
                case "city": City = data; return true;
                case "state": State = data; return true;
                case "postcode": Postcode = data; return true;
                case "email": Email = data; return true;
                case "username": UserName = data; return true;
            }

            return false;
        }
    }

    public sealed class VectorChangedEventArgs : IVectorChangedEventArgs
    {
        public CollectionChange CollectionChange { get; set; }
        public uint Index { get; set; }
    }

    public sealed class DataTemplateModelCollection : IObservableVector<DataTemplateModel>, IList<DataTemplateModel>, INotifyCollectionChanged, IList
    {
        public string Title { get; set; }

        private ObservableCollection<DataTemplateModel> data;
        public event VectorChangedEventHandler<DataTemplateModel> VectorChanged;
        public event NotifyCollectionChangedEventHandler CollectionChanged;

        public DataTemplateModelCollection()
        {
            data = new ObservableCollection<DataTemplateModel>();
            data.CollectionChanged += Data_CollectionChanged;
        }

        private void Data_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (VectorChanged != null)
            {
                VectorChangedEventArgs args = new VectorChangedEventArgs();
                args.CollectionChange = CollectionChange.Reset;
                VectorChanged(this, args);
            }

            if (CollectionChanged != null)
            {
                CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset));
                CollectionChanged(this, e);
            }
        }

        public DataTemplateModel this[int index]
        {
            get { return data[index]; }
            set { data[index] = value; }
        }

        public int Count { get { return data.Count; } }
        public bool IsReadOnly { get { return false; } }
        public void Add(DataTemplateModel item) { data.Add(item); }
        public void Clear() { data.Clear(); }
        public bool Contains(DataTemplateModel item) { return data.Contains(item); }
        public void CopyTo(DataTemplateModel[] array, int arrayIndex) { data.CopyTo(array, arrayIndex); }
        public IEnumerator<DataTemplateModel> GetEnumerator() { return data.GetEnumerator(); }
        public int IndexOf(DataTemplateModel item) { return data.IndexOf(item); }

        public void Insert(int index, DataTemplateModel item)
        {
            data.Insert(index, item);
        }

        public bool Remove(DataTemplateModel item)
        {
            return data.Remove(item);
        }

        public void RemoveAt(int index)
        {
            data.RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return data.GetEnumerator();
        }

        object IList.this[int index]
        {
            get { return data[index]; }
            set { data[index] = (DataTemplateModel)value; }
        }

        int ICollection.Count { get { return data.Count; } }
        bool IList.IsFixedSize { get { return false; } }
        bool ICollection.IsSynchronized { get { return false; } }
        object ICollection.SyncRoot { get { throw new NotImplementedException(); } }
        bool IList.IsReadOnly { get { return false; } }
        bool IList.Contains(object item) { return data.Contains((DataTemplateModel)item); }
        int IList.IndexOf(object item) { return data.IndexOf((DataTemplateModel)item); }
        void IList.Insert(int index, object item) { data.Insert(index, (DataTemplateModel)item); }
        void IList.Remove(object item) { data.Remove((DataTemplateModel)item); }
        void IList.Clear() { data.Clear(); }
        void IList.RemoveAt(int index) { data.RemoveAt(index); }
        void ICollection.CopyTo(Array array, int index) { throw new NotImplementedException(); }

        int IList.Add(object item)
        {
            data.Add((DataTemplateModel)item);
            return data.Count;
        }

    }
}
